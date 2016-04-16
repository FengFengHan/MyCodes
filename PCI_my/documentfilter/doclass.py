import re
import math
from sqlite3 import dbapi2 as sqlite

def sampletrain(c1):
    c1.train('the quick brown fox jumps over the lazy dog', 'good')    
    c1.train('make quick money at the online casino', 'bad')
    c1.train('Nobody owns the water', 'good')
    c1.train('the quick rabbit jumps fence', 'good')
    c1.train('buy pharmac now', 'bad')
    
def getwords(doc):
    splitter = re.compile('\\W*')
    words = [word for word in splitter.split(doc)]

    return dict([(w, 1) for w in words])

class classifier:
    def __init__(self, getfeatures):
        self.fc = {}
        self.cc = {}
        self.getfeatures = getfeatures

    def setdb(self, dbfile):
        self.con = sqlite.connect(dbfile)
        self.con.execute('create table if not exists fc(feature, category, count)')
        self.con.execute('create table if not exists cc(category, count)')

    #increase the count of feautre/cla
    def incf(self, feature, cla):
        count = self.fcount(feature, cla)
        if count == 0:
            self.con.execute("insert into fc values ('%s', '%s', 1)" %(feature, cla))
        else:
            self.con.execute("update fc set count=%d where feature='%s' and category = '%s'"
                             %(count + 1, feature, cla))


    #incrase the count of document that is cla category
    def incc(self, cla):
        count = self.clacount(cla)
        if count == 0:
            self.con.execute("insert into cc values ('%s', 1)" %(cla))
        else:
            self.con.execute("update cc set count=%d where category='%s'" %(count + 1, cla))


    #count of feature f ocuurs in document that is cla category
    def fcount(self, f, cla):
        res = self.con.execute("select count from fc where feature='%s' and category='%s'"
                               %(f, cla)).fetchone()
        if res == None: return 0
        else: return float(res[0])


    #count of document that is cla category

    def clacount(self, cla):
        res = self.con.execute("select count from cc where category='%s'" %(cla)).fetchone()
        if res == None: return 0
        else: return float(res[0])

    # the total count of documnets
    def totalcount(self):
        res = self.con.execute("select sum(count) from cc ").fetchone()
        if res == None: return 0
        else: return res[0]
   # list of category of documents

    def categories(self):
        cur = self.con.execute("select category from cc")
        return [d[0] for d in cur]



    def train(self, item, cla):
        features = self.getfeatures(item)
        for feature in features:
            self.incf(feature, cla)

        self.incc(cla)
        self.con.commit()
    
    #feature f occurs probabilty in  cla  document   
    def fprob(self, f, cla):
        if self.clacount(cla) == 0:
            return 0
        else:
            return self.fcount(f,cla)/self.clacount(cla)
            
    def weighedprob_my(self, f, cat, prf, weight = 1.0, ap = 0.5):
        basicprob = prf(f, cat)
        
        totals = self.cc[cat]
        
        bp = (basicprob * totals + ap * weight)/(weight + totals)
        return bp
         
    def weightedprob(self,f,cat,prf,weight=1.0,ap=0.5):
        # Calculate current probability
        basicprob=prf(f,cat)

        # Count the number of times this feature has appeared in
        # all categories
        totals=sum([self.fcount(f,c) for c in self.categories()])

        # Calculate the weighted average
        bp=((weight*ap)+(totals*basicprob))/(weight+totals)
        return bp




class naivebayes(classifier):
    def __init__(self, getfeatures):
        classifier.__init__(self, getfeatures)
        self.threshold = {}

    # probability of item under cla
    def docprob(self, item, cla):
       features = self.getfeatures(item)
       p = 1
       for feature in features:
           p *= self.weightedprob(feature, cla, self.fprob)
       return p

    #probability of (item, cla)
    def prob(self, item, cla):
        claprob = self.clacount(cla) / self.totalcount()
        docprob = self.docprob(item, cla)
        return claprob * docprob

    def setthreshold(self, cla, t):
        self.threshold[cla] = t

    def getthreshold(self, cla):
        if cla not in self.threshold:return 1.0
        return self.threshold[cla]

    def classify(self, item, default = 'None'):
        probs = {}
        max = 0.0
        for cla in self.cc:
            probs[cla] = self.prob(item, cla)
            if probs[cla] > max:
                max = probs[cla]
                best = cla

        for cla in probs:
            if cla == best: continue
            if probs[cla] * self.getthreshold(best) > probs[best]: return default

        return best

class fisherclassifier(classifier):
    def __init__(self, getfeatures):
        classifier.__init__(self, getfeatures)
        self.minimums = {}

    def setminimum(self, cat, min):
        self.minimums[cat] = min

    def getminimum(self, cat):
        if cat not in self.minimums: return 0.0
        else: return self.minimums[cat]

    def cprob(self, f, cat):
        clf = self.fcount(f, cat)
        if clf == 0:return 0
        freqsum = sum([self.fcount(f, cla) for cla in self.categories()])
        p = clf/freqsum
        return p

    def fisherprob(self, item, cat):
        p = 1
        features =  self.getfeatures(item)
        for feature in features:
            p *= self.weightedprob(feature, cat, self.cprob)

        fscore = -2 * math.log(p)

        return self.invchi2(fscore, len(features) * 2)
    # Use the inverse chi2 function to get a probability
    def invchi2(self,chi, df):
        m = chi / 2.0
        sum = term = math.exp(-m)
        for i in range(1, df//2):
            term *= m / i
            sum += term
        return min(sum, 1.0)

    def classify(self, item, default = None):
        max = 0.0
        best = default
        for cat in self.categories():
            p = self.fisherprob(item, cat)
            if p > self.getminimum(cat) and p > max:
                max = p
                best = cat
        return best





