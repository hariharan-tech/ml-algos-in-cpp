#define PRECISION 0.1f
#define DIM 32
#define ENERGY_FACTOR 0.9f
#define L_MAX 5

void svd(const float a_in[DIM*DIM],float eigval_op[DIM*DIM],float eigvec_op[DIM*DIM]);

void sort_select(const float eigenvec[DIM*DIM],const float eigen[DIM], float sorted_eigenval[DIM],float sorted_eigenvec[DIM*DIM],int& in, float& comp);
