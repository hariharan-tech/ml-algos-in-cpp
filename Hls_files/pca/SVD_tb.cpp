#include<iostream>
#include "SVD_top.h"

//#define DIM 4

int main(void)
{
//  float a[DIM*DIM]= { 10, 2, 3, 4, // testing negative eigenvalue testcase
//                      2, 6, 7, 8,
//                      3, 7, 10, 11,
//                      4, 8, 11, 10};

	float a[DIM*DIM]= { 10, 2, 3, 4,
	                      2, 6, 2, 1,
	                      3, 2, 10, 1,
	                      4, 1, 1, 4};

  float eig_vector[DIM*DIM], eig_value[DIM],sorted_eigenval[DIM],sorted_eigvec[DIM*DIM], comp;
  int index;

    svd(a,eig_value,eig_vector);

	for (int i=0;i<DIM;i++){
		std::cout<<eig_value[i]<<"\t";
  	}
   std::cout<<std::endl;
   sort_select(eig_vector,eig_value,sorted_eigenval,sorted_eigvec,index,comp);
   std::cout<<"Required eigenvalue count: "<<index<<"\nCompression percentage: "<<comp<<std::endl;

	for (int i=0;i<DIM;i++){
		std::cout<<sorted_eigenval[i]<<"\t";
 	}

	std::cout<<std::endl;
	for (int i=0;i<DIM;i++){
			for(int j=0;j<DIM;j++)
				std::cout<<eig_vector[i*DIM+j]<<"\t";
			std::cout<<std::endl;
		 }
	std::cout<<std::endl;
	for (int i=0;i<index;i++){
		for(int j=0;j<DIM;j++)
			std::cout<<sorted_eigvec[i*DIM+j]<<"\t";
		std::cout<<std::endl;
	 }

   return 0;
}
