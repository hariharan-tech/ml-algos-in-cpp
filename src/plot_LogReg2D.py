import csv
import numpy as np
import matplotlib.pyplot as plt
with open("./data/LogReg2D_out.txt","r") as file:
    lines=np.array(list(file.readlines()))
    wline=lines[-1].split()
    a=float(wline[0])
    b=float(wline[1])
    c=float(wline[2])
    # print(a,b,c)
    m=-a/b
    c=-c/b
    # print(m,c)
funcy=lambda x:m*x+c
with open("./data/data_logreg2d.csv","r") as file:
    data=np.array(list(csv.reader(file)),dtype=float)
    # print(data)
    dataT=data.T
    data0xT=dataT[0][dataT[2]==0]
    data0yT=dataT[1][dataT[2]==0]
    data1xT=dataT[0][dataT[2]==1]
    data1yT=dataT[1][dataT[2]==1]
    # print(dataT)
    # print(dataT.shape)
    minx=min(list(dataT[0]))
    maxx=max(list(dataT[0]))
    # x=np.linspace(minx,maxx,1000)
    # print(m,c)
    # y=1/(1+np.exp(-(m*x+c)))
# dataT=lines.T
fig=plt.figure("2-D Logistic Regression")
plt.scatter(data0xT,data0yT,c='g',label="Training data-Class 1")
plt.scatter(data1xT,data1yT,c='b',marker='x',label="Training data-Class 2")
plt.plot([minx,maxx],[funcy(minx),funcy(maxx)],'r',label="Fit")
plt.legend()
# plt.xlabel("x-val")
# plt.ylabel("y-val")
# plt.title("1-D Logistic Regression")
plt.show()