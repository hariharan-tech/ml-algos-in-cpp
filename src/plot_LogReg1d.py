import csv
import numpy as np
import matplotlib.pyplot as plt
with open("./data/LogReg_out.txt","r") as file:
    lines=np.array(list(file.readlines()))
    wline=lines[-1].split()
    m=float(wline[0])
    c=float(wline[1])
    # print(m,c)
# funcy=lambda x:1/(1+np.exp(m*x+c))
with open("./data/data_logreg.csv","r") as file:
    data=np.array(list(csv.reader(file)),dtype=float)
    # print(data)
    dataT=data.T
    # print(dataT)
    # print(dataT.shape)
    minx=min(list(dataT[0]))
    maxx=max(list(dataT[0]))
    x=np.linspace(minx,maxx,1000)
    # print(m,c)
    y=1/(1+np.exp(-(m*x+c)))
# dataT=lines.T
fig=plt.figure("1-D Logistic Regression")
plt.scatter(dataT[0],dataT[1],c='y',label="Training data")
plt.plot(x,y,'r',label="Fit")
plt.legend()
# plt.xlabel("x-val")
# plt.ylabel("y-val")
# plt.title("1-D Logistic Regression")
plt.show()