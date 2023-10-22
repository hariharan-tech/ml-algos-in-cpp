import csv
import numpy as np
import matplotlib.pyplot as plt
with open("./data/LinReg_out.txt","r") as file:
    lines=np.array(list(file.readlines()))
    wline=lines[-1].split()
    m=float(wline[0])
    c=float(wline[1])
    # print(m,c)
funcy=lambda x:m*x+c
with open("./data/data_linreg.csv","r") as file:
    data=np.array(list(csv.reader(file)),dtype=float)
    # print(data)
    dataT=data.T
    # print(dataT)
    # print(dataT.shape)
    minx=min(list(dataT[0]))
    maxx=max(list(dataT[0]))
# dataT=lines.T
plt.figure("Linear Regression")
plt.scatter(dataT[0],dataT[1],c='y',label="Training data")
plt.plot([minx,maxx],[funcy(minx),funcy(maxx)],'r',label="Fit")
plt.legend()
# plt.xlabel("x-val")
# plt.ylabel("y-val")
# plt.title("Linear Regression")
plt.show()