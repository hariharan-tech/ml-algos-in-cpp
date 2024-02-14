#define PRECISION 1f
#define DIM 50
#define ENERGY_FACTOR 0.9f
#define L_MAX 2

//void svd(const float a_in[DIM*DIM],float eigval_op[DIM*DIM],float eigvec_op[DIM*DIM]);
void svd(const float a_in[DIM*DIM],float eigval_op[DIM*DIM],float eigvec_op[DIM*DIM],int count);

void sort_select(const float eigenvec[DIM*DIM],const float eigen[DIM], float sorted_eigenval[DIM],float sorted_eigenvec[DIM*DIM],int& in, float& comp);
