#-*- coding:utf-8 -*-
from numpy import *
from time import sleep

def loadDataSet(filename):
    data = loadtxt(filename)
    return data[:,:2], data[:,2:3].ravel()

def selectJrand(i, m):
    while True:
        j = int(random.uniform(0, m))
        if j != i:
            return j

def clipAlpha(aj, H, L):
    if aj > H:
        aj = H
    if L > aj:
        aj = L
    return aj

def smoSimple(dataMatIn, classLabels, C, toler, maxIter):
    dataMatrix = mat(dataMatIn)
    labelMat   = mat(classLabels).transpose()
    b = 0
    m, n = shape(dataMatrix)
    alphas = mat(zeros((m, 1)))
    iter = 0
    while (iter < maxIter):
        alphaPairsChanged = 0
        for i in range(m):
            fXi = float(multiply(alphas, labelMat).T * (dataMatrix * dataMatrix[i,:].T)) + b
            Ei = fXi - float(labelMat[i])
            if ((labelMat[i] * Ei < -toler) and (alphas[i] < C)) or ((labelMat[i] * Ei > toler) and (alphas[i] > 0)):
                j = selectJrand(i, m)
                fXj = float(multiply(alphas, labelMat).T * (dataMatrix * dataMatrix[j,:].T)) + b
                Ej = fXj - float(labelMat[j])
                alphaIold = alphas[i].copy()
                alphaJold = alphas[j].copy()
                if (labelMat[i] != labelMat[j]):
                    L = max(0, alphas[j] - alphas[i])
                    H = min(C, C + alphas[j] - alphas[i])
                else:
                    L = max(0, alphas[j] + alphas[i] - C)
                    H = min(0, alphas[j] + alphas[i])
                if L == H:
                    print "L == H"
                    continue
                eta = 2.0 * dataMatrix[i,:] * dataMatrix[j,:].T - \
                        dataMatrix[i,:] * dataMatrix[i,:].T - dataMatrix[j,:] * dataMatrix[j,:].T
                if eta >= 0:
                    print "eta >= 0"
                    continue
                alphas[j] -= labelMat[j] * (Ei - Ej) / eta
                alphas[j] = clipAlpha(alphas[j], H, L)
                if (abs(alphas[j] - alphaJold) < 0.00001):
                    print "j not moving enough"
                    continue
                alphas[i] += labelMat[j] * labelMat[i] * (alphaJold - alphas[j])
                b1 = b - Ei - labelMat[i] * (alphas[i] - alphaIold) * dataMatrix[i,:] * dataMatrix[i,:].T - \
                        labelMat[j] * (alphas[j] - alphaJold) * dataMatrix[i,:] * dataMatrix[j,:].T
                b2 = b - Ej - labelMat[i] * (alphas[i] - alphaIold) * dataMatrix[i,:] * dataMatrix[j,:].T - \
                        labelMat[j] * (alphas[j] - alphaJold) * dataMatrix[j,:] * dataMatrix[j,:].T
                if (0 < alphas[i]) and (C > alphas[i]): b = b1
                elif (0 < alphas[j]) and (C > alphas[j]): b = b2
                else: b = (b1 + b2) / 2.0
                alphaPairsChanged += 1
                print "iter: %d i: %d, pairs changed %d" % (iter, i, alphaPairsChanged)
        if (alphaPairsChanged == 0): iter += 1
        else: iter = 0
        print "iteration number: %d" % iter
    return b, alphas

def plotSupportVectors(data, labels, b, alphas):
    import matplotlib.pyplot as plt
    fig = plt.figure()
    ax = fig.add_subplot(111)
    data1 = data[where(labels==1)]
    data2 = data[where(labels==-1)]
    ax.scatter(data1[:,0], data1[:,1], marker='s', s=90)
    ax.scatter(data2[:,0], data2[:,1], marker='o', s=50, c='red')
    w1, w2 = dot((tile(labels.reshape(1, -1).T, (1, 2)) * data).T, array(alphas)).ravel()
    b = float(b)
    x = [data.max(axis=0)[0], data.min(axis=0)[0]]
    y = [(-b - w1 * x[0]) / w2, (-b - w1 * x[1]) / w2] 
    ax.plot(x, y)
    sv = data[where(alphas>0)]
    ax.scatter(sv[:,0], sv[:,1], s=150, c='none', edgecolor='green')
    plt.show()
