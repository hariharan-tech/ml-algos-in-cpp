import numpy as np
import csv
import matplotlib.pyplot as plt
low=4*np.random.random(500)
high=6+5*np.random.random(500)
xval=np.concatenate((low,high))
labels=np.concatenate((np.zeros(500),np.ones(500)))
data=np.array([xval,labels]).T
with open("./data/data_logreg.csv","w") as file:
    fw=csv.writer(file)
    fw.writerows(data)
plt.scatter(xval,labels)
plt.show()