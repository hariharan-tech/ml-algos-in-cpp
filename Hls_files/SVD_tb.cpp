#include "SVD_top.cpp"
#include<iostream>

#define DIM 4

int main(void)
{
  float a[DIM*DIM]= { 10, 2, 3, 4,
                      2, 6, 7, 8,
                      3, 7, 10, 11,
                      4, 8, 11, 10,};

  float eig_vector[DIM*DIM];

  svd(a,eig_vector);

  for (int i=0; i<DIM; i++)
  {
    for (int j=0;j<DIM;j++)
      std::cout<<a[i*DIM+j]<<" ";
    std::cout<<std::endl;
  }
}
