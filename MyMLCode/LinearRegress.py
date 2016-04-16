from sklearn import linear_model
from numpy import *

def loadData(fileName):
    f = open(fileName)
    dataMat = []
    lableMat = []
    numFea = len((f.readline().strip()).split("\t")) - 1
    for line in f.readlines():
        nums = line.strip().split("\t")
        lineFea = []
        for i in range(numFea):
            lineFea.append(float(nums[i]))
        dataMat.append(lineFea)
        lableMat.append(float(nums[numFea]))
    return dataMat,lableMat

def standLinearRes(xArr,yArr):
    X = mat(xArr)
    Y = mat(yArr).T
    xTx = X.T.dot(X)
    if linalg.det(xTx) == 0:
        print("X is not sigular",end = "\n")
    res = xTx.I.dot(X.T.dot(Y))
    return res

# x_train, y_train = loadData('ex0.txt')
# x_test = [0, 0.5]
# linear = linear_model.LinearRegression()
# linear.fit(x_train,y_train)
# print("coef:", linear.coef_)
# print("interpt:", linear.intercept_)
# y_test = linear.predict(x_test)
# print(y_test)
xArr = [[1, 1], [2,1], [4,1], [0,1]]
yArr = [0.5, 1, 2, 0]
res = standLinearRes(xArr, yArr)
print(res)
