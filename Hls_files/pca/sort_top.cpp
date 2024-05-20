#include "SVD_top.h"
#include "sort.hpp"

void sort_select(const float eigenvec[DIM*DIM],const float eigen[DIM], float sorted_eigenval[DIM],float sorted_eigenvec[DIM*DIM],int& in, float& comp)
{
	int sorted_index[DIM],index;
	float sorted_eig_buff[DIM],eigen_val[DIM];

    for (int i=0;i<DIM;i++)
    	eigen_val[i]=eigen[i];


	sort_desc<DIM>(eigen_val,sorted_eig_buff, sorted_index);
	energy_index_count<DIM>(sorted_eig_buff,index,comp);
	sort_eigenvector<DIM>(eigenvec,sorted_index,index,sorted_eigenvec);

	WRITE_SORTED_EIGENVAL:for(int i=0;i<DIM;i++)
	{
		sorted_eigenval[i] = sorted_eig_buff[i];
	}
	in = index;
}

