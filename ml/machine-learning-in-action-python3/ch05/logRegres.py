import numpy as np

def loadDataSet():
    data = np.loadtxt('testSet.txt.gz')
    return np.insert(data[:,:2], 0, 1.0, axis=1), data[:,2:3].ravel() 

def sigmoid(inX):
    return 1.0 / (1.0 + np.exp(-inX))

def gradAscent(dataMatIn, classLabels):
    dataMatrix  = np.matrix(dataMatIn)
    labelMatrix = np.matrix(classLabels).transpose()
    weights = np.ones((dataMatrix.shape[1], 1))
    for i in range(500):
        error = labelMatrix - sigmoid(dataMatrix * weights)
        weights = weights + 0.001 * dataMatrix.transpose() * error
    return weights

def plotBestFit(weights):
    import matplotlib.pyplot as plt
    data, labels = loadDataSet()
    xcord1 = []
    ycord1 = []
    xcord2 = []
    ycord2 = []
    for i in range(data.shape[0]):
        if int(labels[i]) == 1:
            xcord1.append(data[i,1])
            ycord1.append(data[i,2])
        else:
            xcord2.append(data[i,1])
            ycord2.append(data[i,2])
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.scatter(xcord1, ycord1, s=30, c='red', marker='s')
    ax.scatter(xcord2, ycord2, s=30, c='green')
    x = np.arange(-3.0, 3.0, 0.1)
    y = (-weights[0] -weights[1] * x) / weights[2]
    ax.plot(x, y)
    plt.xlabel('X1')
    plt.ylabel('X2')
    plt.show()

def stocGradAscent0(dataMatrix, classLabels):
    weights = np.ones(dataMatrix.shape[1])
    for i in range(dataMatrix.shape[0]):
        error = classLabels[i] - sigmoid(np.sum(dataMatrix[i] * weights))
        weights = weights + 0.01 * dataMatrix[i] * error
    return weights

def stocGradAscent1(dataMatrix, classLabels, numIter=150):
    weights = np.ones(dataMatrix.shape[1])
    for i in range(numIter):
        for j in range(dataMatrix.shape[0]):
            index = int(np.random.uniform(0, dataMatrix.shape[0]))
            error = classLabels[index] - sigmoid(np.sum(dataMatrix[index] * weights))
            weights = weights + (4 / (1.0 + j + i) + 0.0001) * dataMatrix[index] * error 
    return weights
