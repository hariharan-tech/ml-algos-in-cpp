#include<iostream>
#include "SVD_top.h"
//#define DIM 4

int main(void)
{
  float a[DIM*DIM]= { 10, 2, 3, 4,
                      2, 6, 7, 8,
                      3, 7, 10, 11,
                      4, 8, 11, 10};

  float eig_vector[DIM*DIM], eig_value[DIM],sorted_eigen[DIM];

    svd(a,eig_value,eig_vector);

	for (int i=0;i<DIM;i++){
		std::cout<<eig_value[i]<<"\t";
  	}
   std::cout<<std::endl;
   sort_select(eig_vector,eig_value,sorted_eigen);

	for (int i=0;i<DIM;i++){
		std::cout<<sorted_eigen[i]<<"\t";
 	}

   return 0;
}
