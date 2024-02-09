#include "SVD_top.h"
#include "sort.hpp"

void sort_select(const float eigenvec[DIM*DIM],const float eigen[DIM], float sorted_eigen[DIM])
{
	int sorted_index[DIM];
	float sorted_eig_buff[DIM],eigen_val[DIM];
	int ind;

//    for (int i=0;i<DIM;i++)
//    	eigen_val[i]=eigen[i];


	sort_desc<DIM>(eigen,sorted_eig_buff, sorted_index);
	//energy_index_count<DIM>(sorted_eig_buff,ind);

	for(int i=0;i<DIM;i++)
	{
		sorted_eigen[i]=sorted_eig_buff[i];
	}

}

