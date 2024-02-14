# This script generates the golden test vectors for PCA for a given Dimension

DIM = 4
TEST_VECTOR_COUNT = 10
LOC = ".\..\Hls_files\pca\\"
INPUT_FILE_NAME = f"{LOC}input_vector_{DIM}x{DIM}.h"
OUTPUT_FILE_NAME = f"{LOC}output_vector_{DIM}x{DIM}.h"

import numpy as np

with open(INPUT_FILE_NAME,"w") as in_vec:
    in_vec.write(f"float input_vector[{TEST_VECTOR_COUNT}][{DIM*DIM}] = "+"{")
with open(OUTPUT_FILE_NAME,"w") as out_vec:
    out_vec.write(f"float output_vector[{TEST_VECTOR_COUNT}][{DIM}] = "+"{")

temp = 0

while True:
    a = np.random.rand(DIM,DIM).astype(np.float32)
    b = np.tril(a)+np.triu(np.transpose(a),1)
    if((b==np.transpose(b)).all()):
        temp +=1
        eigval = -np.sort(np.linalg.eig(-b)[0])
        with open(INPUT_FILE_NAME,"a") as in_vec:
            in_vec.write("{"+f"{np.array2string(b.reshape(1,-1),max_line_width=None,separator=',')[2:-2]}"+"},\n")
        with open(OUTPUT_FILE_NAME,"a") as out_vec:
            out_vec.write("{"+f"{np.array2string(eigval.reshape(1,-1),max_line_width=None,separator=',')[2:-2]}"+"},\n")

    if temp >= TEST_VECTOR_COUNT:
        break

with open(INPUT_FILE_NAME,"a") as in_vec:
    in_vec.write("};")
with open(OUTPUT_FILE_NAME,"a") as out_vec:
    out_vec.write("};")
print("\n====Input and output testvectors are generated!====\n")