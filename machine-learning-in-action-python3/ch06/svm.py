import numpy as np

# 加载测试数据
def loadDataSet():
    data = np.loadtxt('testSet.txt.gz')
    return data[:,0:2], data[:,2]


# 随机选择一个不等于 i 的索引
def selectJrand(i, m):
    while True:
        j = int(np.random.uniform(0, m))
        if j != i: return j


# 裁剪alpha值, 使其落在L和H范围内
def clipAlpha(alpha, L, H):
    if alpha < L:
        return L
    elif alpha > H:
        return H
    else:
        return alpha


# SMO算法的简单实现版
def smoSimple(data, labels, C, toler):

    # 初始化alpha向量和截距b
    alphas = np.zeros(data.shape[0]); b = 0
    while True:
        changed = False
        for i in range(data.shape[0]):

            # 计算误差Ei
            Ei = (alphas * labels * (data[i] * data).sum(axis=1)).sum() + b - labels[i]

            # 是否满足KTT条件
            if (labels[i] * Ei < -toler and alphas[i] < C
                or
                labels[i] * Ei > toler  and alphas[i] > 0):

                # 随机选择一个j
                j = selectJrand(i, data.shape[0])

                # 计算误差Ej
                Ej = (alphas * labels * (data[j] * data).sum(axis=1)).sum() + b - labels[j]

                # 保存老alphas[i]和alphas[j]
                alphaIold = alphas[i].copy()
                alphaJold = alphas[j].copy()

                # 计算新alphas[j]的上界和下界
                if labels[i] == labels[j]:
                    L = max(0, alphaIold + alphaJold - C)
                    H = min(C, alphaIold + alphaJold)
                else:
                    L = max(0, alphaJold - alphaIold)
                    H = min(C, alphaJold - alphaIold + C)
                
                # 计算eta
                eta = np.inner(data[i], data[i]) + np.inner(data[j], data[j]) - \
                        2 * np.inner(data[i], data[j])

                # 计算和裁剪新的alphas[j]、alphas[i]
                alphas[j] = clipAlpha(alphaJold + labels[j] * (Ei - Ej) / eta, L, H)
                alphas[i] = alphaIold + labels[i] * labels[j] * (alphaJold - alphas[j])

                # 计算截距b
                Bi = b - Ei - labels[i] * (alphas[i] - alphaIold) * np.inner(data[i], data[i]) \
                            - labels[j] * (alphas[j] - alphaJold) * np.inner(data[i], data[j])
                Bj = b - Ej - labels[j] * (alphas[j] - alphaJold) * np.inner(data[j], data[j]) \
                            - labels[i] * (alphas[i] - alphaIold) * np.inner(data[j], data[i])
                if alphas[i] > 0 and alphas[i] < C:
                    b = Bi
                elif alphas[j] > 0 and alphas[j] < C:
                    b = Bj
                else:
                    b = (Bi + Bj) / 2.0

                # 更改状态标识
                changed = True
        
        # 如果遍历完一圈没有更新, 退出循环
        if not changed: break

    return b, alphas


# 可视化
def plot(data, labels, b, alphas):
    import matplotlib.pyplot as plt
    fig = plt.figure()
    ax = fig.add_subplot(111)
    # 画点
    data1 = data[np.where(labels==1)]
    data2 = data[np.where(labels==-1)]
    ax.scatter(data1[:,0], data1[:,1], marker='s', c='orange')
    ax.scatter(data2[:,0], data2[:,1], marker='o', c='blue')
    # 画分隔线
    w = (labels * alphas * data.T).sum(axis=1)
    x = np.array([data[:,0].min(), data[:,0].max()])
    y = (-np.array([b, b]) - w[0] * x) / w[1]
    ax.plot(x, y)
    # 标记支持向量
    sv = data[np.where(alphas>0)]
    ax.scatter(sv[:,0], sv[:,1], s=150, c='none', edgecolor='red')
    plt.show()
