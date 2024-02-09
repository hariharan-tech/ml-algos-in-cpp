#define PRECISION 1.0f
#define DIM 4

void svd(const float a_in[DIM*DIM],float eigval_op[DIM*DIM],float eigvec_op[DIM*DIM]);

void sort_select(const float eigenvec[DIM*DIM],const float eigen[DIM], float sorted_eigen[DIM]);
