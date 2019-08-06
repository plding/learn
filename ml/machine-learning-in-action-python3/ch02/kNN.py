import numpy as np

def createDataSet():
    group  = np.array([[1.0, 1.1], [1.0, 1.0], [0, 0], [0, 0.1]])
    labels = ['A', 'A', 'B', 'B']
    return group, labels

def classify0(inX, dataSet, labels, k):
    distances = ((dataSet - inX) ** 2).sum(axis=1) ** 0.5
    indices   = distances.argsort()[:k]
    classCount = {}
    for index in indices:
        classCount.setdefault(labels[index], 0)
        classCount[labels[index]] += 1
    return sorted(classCount.items(), key=lambda x: x[1], reverse=True)[0][0]

def file2matrix(filename):
    matrix = np.loadtxt(filename)
    return matrix[:,:3], matrix[:,3:4].ravel()

def autoNorm(dataSet):
    minVals = dataSet.min(0)
    maxVals = dataSet.max(0)
    ranges  = maxVals - minVals
    return (dataSet - minVals) / ranges, ranges, minVals

def datingClassTest():
    datingData, datingLabels = file2matrix('datingTestSet.txt.gz')
    normMat, _, _ = autoNorm(datingData) 
    testNum  = int(normMat.shape[0] * 0.1)
    errorNum = 0
    for i in range(testNum):
        result = classify0(normMat[i,:], normMat[testNum:,:], datingLabels[testNum:], 3)
        print("the classifier came back with: %d, the real answer is: %d" % (result, datingLabels[i]))
        if (result != datingLabels[i]): errorNum += 1
    print("the total test is: %d, error is: %d, error rate is: %f" % (testNum, errorNum, errorNum / testNum))
