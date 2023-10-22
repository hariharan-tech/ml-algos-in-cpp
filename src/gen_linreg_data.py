import numpy as np
import csv
import matplotlib.pyplot as plt
noise=np.random.randn(500)
x=np.linspace(1,10,500)
# y=3*x+5+noise
y=4*x+10+noise
data=np.array([x,y]).T
# data=np.concatenate((x,y),axis=1)
print(data)
plt.scatter(x,y)
plt.show()
with open("./data/data_reg.csv","w") as file:
    fw=csv.writer(file)
    fw.writerows(list(data))