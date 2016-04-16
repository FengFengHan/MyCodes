#coding:utf-8

import  urllib2
import re
from bs4 import BeautifulSoup
from urlparse import  urljoin
from sqlite3 import dbapi2 as sqlite

ignorewords = set(['the','of','to','and','a','in','is','it'])

class crawler:
    # Initilization of class of crawler
    def __init__(self,dbname):
        self.con = sqlite.connect(dbname)

    def __del__(self):
        self.con.close()

    def dbcommit(self):
        self.con.commit()

    def createindextables(self):
        self.con.execute('create table urllist(url)')
        self.con.execute('create table wordlist(word)')
        self.con.execute('create table wordlocation(urlid,wordid,location)')
        self.con.execute('create table link(fromid integer,toid integer)')
        self.con.execute('create table linkwords(wordid,linkid)')
        self.con.execute('create index urlidx on urllist(url)')
        self.con.execute('create index wordidx on wordlist(word)')
        self.con.execute('create index wordurlidx on wordlocation(wordid)')
        self.con.execute('create index urltoidx on link(toid)')
        self.con.execute('create index urlfromidx on link(fromid)')
        self.dbcommit()

    # get id of entry
    def getentryid(self,table,field,value,createnew = True):
        cur = self.con.execute("select rowid from %s where %s='%s'"%(table,field,value))
        res = cur.fetchone()
        if res == None:
            cur = self.con.execute("insert into %s (%s) values ('%s')" %(table,field,value))
            return cur.lastrowid
        else:
            return res[0]

    #build index for url and word
    def addtoindex(self,url,soup):
        if self.isindexed(url):return
        print 'Indexing %s' %url

        #achive for every word
        text = self.gettextonly(soup)
        words = self.separatewords(text)

        #achive  index for url
        urlid = self.getentryid('urllist','url',url)

        #achive relation between urlid an wordid
        for i in range(len(words)):
            word = words[i]
            if word in ignorewords:continue
            wordid = self.getentryid('wordlist','word',word)
            self.con.execute("insert into wordlocation(urlid,wordid,location) \
                             values (%d,%d,%d)" %(urlid,wordid,i)
                             )


    #get text from HTML
    def gettextonly(self,soup):
        v = soup.string
        if v==None:
            c = soup.contents
            resultext = ''
            for t in c:
                subtext = self.gettextonly(t)
                resultext += subtext + '\n'
            return resultext
        else:
            return v.strip()


    #split words by non-space
    def separatewords(self,text):
        splitter = re.compile('\\W*')
        return [s.lower() for s in splitter.split(text) if s != '']

    # 如果已经建立过索引，返回True
    def isindexed(self,url):
        u = self.con.execute \
                ("select rowid from urllist where url='%s'" %url).fetchone()
        if u != None:
            v=self.con.execute \
                    ('select * from wordlocation where urlid=%d' %u[0]).fetchone()
            if v != None:
                return True
        return False

    #添加一个俩个网页的链接
    def addlinkref(self,urlFrom,urlTo,linkText):
        words=self.separateWords(linkText)
        fromid=self.getentryid('urllist','url',urlFrom)
        toid=self.getentryid('urllist','url',urlTo)
        if fromid==toid: return
        cur=self.con.execute("insert into link(fromid,toid) values (%d,%d)" % (fromid,toid))
        linkid=cur.lastrowid
        for word in words:
          if word in ignorewords: continue
          wordid=self.getentryid('wordlist','word',word)
          self.con.execute("insert into linkwords(linkid,wordid) values (%d,%d)" % (linkid,wordid))

    #从一小组网页开始进行广度收索，直到某一深度
    def crawl(self,pages,depth = 2):
        for i in range(depth):
            newpages = set()
            for page in pages:
                try:
                    c = urllib2.urlopen(page)
                except:
                    print 'could not open %s' %page
                    continue
                soup = BeautifulSoup(c.read())
                self.addtoindex(page,soup)

                links = soup.find_all('a')
                for link in links:
                    if('href' in dict(link.attrs)):
                        url = urljoin(page,link['href'])
                        if url.find("'") != -1: continue
                        url = url.split('#')[0]
                        if url[0:4] == 'http' and not self.isindexed(url):
                            newpages.add(url)
                        linkText = self.gettextonly(link)
                        self.addlinkref(page,url,linkText)
                self.dbcommit()
            pages = newpages


class searcher:
    def __init__(self,dbname):
        self.con = sqlite.connect(dbname)
    def __del__(self):
        self.con.close()

    def getmatchrows(self,q):
        #构造查询的字符串
        fieldlist = 'w0.urlid'
        tablelist = ''
        clauselist = ''
        wordids = []

        #根据空格拆分单词
        words = q.split(' ')
        tablenumber = 0
        for word in words:
            wordrow = self.con.execute(
                "select rowid from wordlist where word = '%s'" % word
            ).fetchone()
            if wordrow != None:
                wordid = wordrow[0]
                wordids.append(wordid)
                if tablenumber > 0:
                    tablelist += ','
                    clauselist += ' and '
                    clauselist += 'w%d.urlid=w%d.urlid and '% (tablenumber -1,tablenumber)
                fieldlist += ',w%d.location' % tablenumber
                tablelist += 'wordlocation w%d' % tablenumber
                clauselist += 'w%d.wordid=%d' % (tablenumber,wordid)
                tablenumber += 1
        # else:
        #     print 'clauselist: '
        #     print clauselist
        fullquery = 'select %s from %s where %s'% (fieldlist,tablelist,clauselist)
        print 'fullquery: ',
        print fullquery
        cur = self.con.execute(fullquery)
        rows = [row for row in cur]
        return rows,wordids

    def query(self,q):
        rows,wordids = self.getmatchrows(q)
        scores = self.getscoredlist(rows,wordids)
        rankedscores = sorted([(score,url) for (url,score) in scores.items()],reverse = 1)
        for (score,url) in rankedscores[0:10]:
            print '%f\t%s'%(score,self.geturlname(url))

    def getscoredlist(self,rows,wordids):
        totalscores = dict([(row[0],0) for row in rows])
        #评价函数
        # weights = [(1.0,self.frequencyscore(rows)),
        #     (1.5,self.locationscore(rows))]
        weights = [(1.0,self.distancescore(rows))]
        for (weight,scores) in weights:
            for url in totalscores:
                totalscores[url] += weight * scores[url]
        return totalscores
    def geturlname(self,id):
        return self.con.execute("select url from urllist where rowid=%d" % id).fetchone()[0]

    def normalizescores(self,scores,smallIsBetter=0):
        vsmall=0.00001
        if smallIsBetter:
            minscore = min(scores.values())
            return dict([(u,float(minscore)/max(vsmall,l)) for (u,l) in scores.items()])
        else:
            maxscore = max(scores.values())
            if maxscore == 0: maxscore = vsmall
            return dict([(u,float(l)/maxscore) for (u,l) in scores.items()])

    def frequencyscore(self,rows):
        counts = dict([(row[0],0) for row in rows])
        for row in rows:
            counts[row[0]] += 1
        return self.normalizescores(counts)

    def locationscore(self,rows):
        #初始化一个很大的值
        locations = dict([(row[0],1000000) for row in rows])

        for row in rows:
            loc = sum(row[1:])
            if loc < locations[row[0]]: locations[row[0]] = loc
        return self.normalizescores(locations,smallIsBetter=1)

    def distancescore(self,rows):
        if(len(rows[0]) <= 2): return dict([(row[0],1.0) for row in rows])
        #初始化一个很大的值
        mindistances = dict([(row[0],1000000) for row in rows])

        for row in rows:
            dist = sum([abs(row[i] - row[i -1]) for i in range(2,len(row))])
            if dist < mindistances[row[0]]:
                mindistances[row[0]] = dist
        return self.normalizescores(mindistances,smallIsBetter=1)
#cr = crawler('searchengine.db')
#cr.createindextables()
#pagelist = ['http://en.wikipedia.org/wiki/Python','http://en.wikipedia.org/wiki/CMU_Common_Lisp']
#cr.crawl(pagelist)
e = searcher('searchindex.db')
# rows,wordids = e.getmatchrows('functional programming')
# print rows
e.query('functional programming')
#del crawler





