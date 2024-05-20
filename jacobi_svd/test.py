import sys
import ctypes
import numpy as np

a = np.array([1, 2, 3, 4, 5,
            2, 6, 7, 8, 9,
            3, 7, 10, 11, 12,
            4, 8, 11, 13, 14,
            5,9,12,14,15]).reshape((5,5))
eigval, eigvec = np.linalg.eig(a);
print(f"Eigenvalues {eigval}\n\n Eigenvector:\n{eigvec}")