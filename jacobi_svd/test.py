import sys
import ctypes
import numpy as np

a = np.array(eval(sys.argv[1]),dtype=np.float32)
eigval, eigvec = np.linalg.eig(a);
print(f"Eigenvalues {eigval}\n\n Eigenvector:\n{eigvec[:,0]}\n{eigvec[:,1]}")