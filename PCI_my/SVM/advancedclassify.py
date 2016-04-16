__author__ = 'Administrator'

from pylab import *
import math
class matchrow:
    def __init__(self, row, allnum = False):
        if allnum:
            self.data = [float(row[i]) for i in range(len(row) - 1)]
        else:
            self.data = row[0:len(row) - 1]
        self.match = int(row[len(row) - 1])

def loadmatch(f, allnum = False):
    rows = []
    for line in file(f):
        rows.append(matchrow(line.split(','), allnum))
    return rows

def plotagematches(rows):
    xdm = [row.data[0] for row in rows if row.match == 1]
    ydm = [row.data[1] for row in rows if row.match == 1]
    xdn = [row.data[0] for row in rows if row.match == 0]
    ydn = [row.data[1] for row in rows if row.match == 0]
    plot(xdm, ydm, 'go')
    plot(xdn, ydn, 'ro')

    show()
loadmatch("agesonly.csv")

'''
linear classify
'''
def lineartrain(rows):
    averages = {}
    counts = {}
    for row in rows:
        cla = row.match
        averages.setdefault(cla, [0.0]*len(row.data))
        counts.setdefault(cla, 0)

        #join the point to averages and counts
        for i in range(len(row.data)):
            averages[cla][i] += float(row.data[i])
        counts[cla] += 1

    #compute the mean value
    for cla in counts.keys():
        for i in range(len(averages[cla])):
            averages[cla][i] /= counts[cla]

    return averages
def dpproduct(v1, v2):
    return sum([v1[i]*v2[i] for i in range(len(v1))])
    
def dpclassify(point, avgs):
    midCla = [(avgs[0][i] + avgs[1][i])/2.0 for i in range(len(avgs[0]))]
    clasV = [(avgs[1][i] - avgs[0][i]) for i in range(len(avgs[0]))]
    pointMV = [(midCla[i] - point[i]) for i in range(len(midCla))]
    y = dpproduct(clasV, pointMV)
    if y > 0: return 0
    else: return 1

'''
format data to numeric
'''
def yesno(v):
    if v == 'yes': return 1
    elif v == 'no': return -1
    else: return 0
        
def matchcount(interset1, interset2):
    in1 = interset1.split(',')
    in2 = interset2.split(',')
    x = 0
    for v in in1:
        if v in in2:
            x += 1
    return x

def milesdistance(a1, a2):
    return 0
        
def loadnumeric():
    oldrows = loadmatch('matchmaker.csv')
    newrows = []
    for row in oldrows:
        d = row.data
        data = [float(d[0]), yesno(d[1]), yesno(d[2]),
                float(d[5]), yesno(d[6]), yesno(d[7]),
                matchcount(d[3], d[8]),
                milesdistance(d[4], d[9]),
                row.match]
        newrows.append(data)
    return newrows

def scaledata(rows):
    low = [99999999.0] *len(rows[0].data)
    high = [-99999999.0]*len(rows[0].data)
    for row in rows:
        d = row.data
        # find max  and min
        for i in range(len(d)):
            if d[i] > high[i]: high[i] = d[i]
            if d[i] < low[i]: low[i] = d[i]

    def scaleinput(d):
        length = len(d)
        result = []
        for i in range(length):
            if high[i] == low[i]:
                result.append(1.0)
            else:
                result.append((d[i] - low[i])/(high[i] - low[i]))
        return  result

    return [matchrow(scaleinput(row.data) + [row.match]) for row in rows]

'''
kernel technique
'''
def vecl2(v):
    return sum([v[i] ** 2 for i in range(len(v))])

def rbf(v1, v2, gamma = 20):
    dv = [v1[i] - v2[i] for i in range(len(v1))]
    L2 = vecl2(dv)
    return math.e ** (-L2 * gamma)

def getoffset(rows, gamma = 10):
   l0 = []
   l1 = []

   for row in rows:
       cla = row.match
       if cla == 0:
           l0.append(row.data)
       else:
           l1.append(row.data)
   sum0 = sum( [sum([rbf(v1, v2, gamma) for v1 in l0]) for v2 in l0])
   sum1 = sum( [sum([rbf(v1, v2, gamma) for v1 in l1]) for v2 in l1])

   return (((1.0/len(l1)) ** 2) * sum1 - ((1.0/len(l0)) ** 2) * sum0)/2.0

def nclassify(point, rows, offset, gamma = 10):
    sum0 = 0.0
    count0 = 0
    sum1 = 0.0
    count1 = 0

    for row in  rows:
        cla = row.match
        if cla == 0:
            sum0 += rbf(point, row.data, gamma)
            count0 += 1
        else:
            sum1 += rbf(point, row.data, gamma)
            count1 += 1

    y = (1.0/count0)*sum0 - (1.0/count1)*sum1 + offset

    if y > 0: return  0
    else: return 1







    

