#define PRECISION 0.1f
#define DIM 25
#define ENERGY_FACTOR 0.9f
#define L_MAX 10

void pca(const float a_in[DIM*DIM],float sorted_eigvec[L_MAX*DIM],int &index_count, float &comp_rate);

//void sort_select(const float eigenvec[DIM*DIM],const float eigen[DIM], float sorted_eigenval[DIM],float sorted_eigenvec[DIM*DIM],int& in, float& comp);
