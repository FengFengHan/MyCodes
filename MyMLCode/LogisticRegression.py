import numpy as np

def loadData(fileName):
    f = open(fileName)
    data = []
    lable = []
    numFea = len((f.readline().strip()).split("\t")) - 1
    for line in f.readlines():
        nums = line.strip().split("\t")
        lineFea = []
        lineFea.append(1)
        for i in range(numFea):
            lineFea.append(float(nums[i]))
        data.append(lineFea)
        lable.append(float(nums[numFea]))
    return data,lable

def logisticFun(x):
    return 1/(1+ np.exp(-x))

def getGradeMat(dataMat, labelMat, weights):
     h = logisticFun(dataMat.dot(weights))
     grade = (dataMat.T).dot((labelMat - h).reshape(-1,1))
     return  grade

def getGrade(data,label,weights):
    h = logisticFun(data.dot(weights))
    grade = ((label -h) * data).reshape(-1,1)
    return grade

def gradeDescent(dataMat, labelMat, getGrade,minValue = True,alpha = 0.001,maxRecycle = 500):
    flag = -1 if minValue else 1
    m,n = dataMat.shape
    weights = np.ones((n,1))
    for k in range(maxRecycle):
        grade = getGrade(dataMat,labelMat,weights)
        weights = weights + flag * alpha * grade
    return weights

def  stacGradeDescent(dataMat, labelMat, getGrade,minValue = True,alpha = 0.001,numIter = 500):
    flag = -1 if minValue else 1
    m,n = dataMat.shape
    weights = np.ones((n,1))
    for _ in range(numIter):
        for i in range(m):
            grade = getGrade(dataMat[i],labelMat[i],weights)
            weights = weights + flag * alpha * grade
    return weights


fileName = 'textSet.txt'
data, label = loadData(fileName)
dataMat = np.array(data)
labelMat = np.array(label)
labelMat.resize(len(label),1)
weights1 = gradeDescent(dataMat,labelMat,getGradeMat,minValue = False)
weights2 = stacGradeDescent(dataMat,labelMat,getGrade,minValue = False)
print('end')