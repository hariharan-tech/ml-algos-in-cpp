import numpy as np
import csv
import matplotlib.pyplot as plt
# low=4*np.random.random(500)
# high=6+5*np.random.random(500)
# xval=np.concatenate((low,high))
mean1=np.array([1,2])
b1=np.random.multivariate_normal(mean1,25*np.identity(2),500)
mean2=np.array([10,-10])
b2=np.random.multivariate_normal(mean2,16*np.identity(2),500)
xval=np.concatenate((b1,b2))
labels=np.concatenate((np.zeros(500),np.ones(500)))
# print(xval.T)
# print(labels)
# print(xval.shape,labels.shape)
data=np.concatenate((xval.T,np.reshape(labels,(1,1000)))).T  
with open("./data/data_logreg2d.csv","w") as file:
    fw=csv.writer(file)
    fw.writerows(data)
fig=plt.figure()
plt.scatter((b1.T)[0],(b1.T)[1],c='g')
plt.scatter((b2.T)[0],(b2.T)[1],marker='x')
plt.show()