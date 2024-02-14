import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

df_4 = pd.read_csv("./iteration_analysis/abs_loss4.csv")
df_10 = pd.read_csv("./iteration_analysis/abs_loss10.csv")
df_20 = pd.read_csv("./iteration_analysis/abs_loss20.csv")
# df_4 = pd.read_csv("./iteration_analysis/abs_loss4.csv")
f = open("./iteration_analysis/abs_loss50.txt")
x_axis50 = f.readlines()[0]
vals = f.readlines()[1]
f.close()

x_axis = np.array(list(df_4.columns.values),dtype=np.int32)
abs_diff = df_4.mean().to_numpy()
plt.scatter(x_axis/16,abs_diff/max(abs_diff))

x_axis = np.array(list(df_10.columns.values),dtype=np.int32)
abs_diff = df_10.mean().to_numpy()
plt.scatter(x_axis/100,abs_diff/max(abs_diff))

x_axis = np.array(list(df_20.columns.values),dtype=np.int32)
abs_diff = df_20.mean().to_numpy()
plt.scatter(x_axis/400,abs_diff/max(abs_diff))

abs_diff = np.array(eval(f"[{vals}]"),dtype=np.float32)
x_axis = np.array()
print(x_axis.shape,abs_diff.shape)
plt.scatter(x_axis/2500,abs_diff/max(abs_diff))

plt.show()