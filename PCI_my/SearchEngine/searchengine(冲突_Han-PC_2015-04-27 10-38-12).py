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
        pass

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
        fieldlist = 'wo.urlid'
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

        fullquery = 'select %s from %s where %s'% (fieldlist,tablelist,clauselist)
        cur = self.con.execute(fullquery)
        rows = [row for row in cur]

        return rows,wordids
cr = crawler('searchengine.db')
cr.createindextables()
pagelist = ['http://en.wikipedia.org/wiki/Python']
cr.crawl(pagelist)
#e = searcher('searchengine.db')
#e.getmatchrows('Python Python')
#del crawler





