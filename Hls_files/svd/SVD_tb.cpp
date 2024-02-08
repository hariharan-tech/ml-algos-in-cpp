#include<iostream>
#include "SVD_top.h"

//#define DIM 4

int main(void)
{
  float a[DIM*DIM]= { 10, 2, 3, 4,
                      2, 6, 7, 8,
                      3, 7, 10, 11,
                      4, 8, 11, 10};

  float eig_vector[DIM*DIM], eig_value[DIM*DIM];

  svd(a,eig_value,eig_vector);

  for (int i=0; i<DIM; i++)
  {
    for (int j=0;j<DIM;j++)
      std::cout<<eig_value[i*DIM+j]<<" ";
    std::cout<<std::endl;
  }
}
