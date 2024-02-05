#include<iostream>
#include "SVD_top.h"

#define DIMEN 4

int main(void)
{
  float a[DIMEN*DIMEN]= { 10, 2, 3, 4,
                      2, 6, 7, 8,
                      3, 7, 10, 11,
                      4, 8, 11, 10};

  float eig_vector[DIMEN*DIMEN], eig_value[DIMEN*DIMEN];

  svd(a,eig_value,eig_vector);

  for (int i=0; i<DIMEN; i++)
  {
    for (int j=0;j<DIMEN;j++)
      std::cout<<eig_value[i*DIMEN+j]<<" ";
    std::cout<<std::endl;
  }
}
