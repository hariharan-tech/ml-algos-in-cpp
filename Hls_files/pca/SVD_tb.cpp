#include<iostream>
#include "SVD_top.h"

//#define DIM 4

int main(void)
{
//  float a[DIM*DIM]= { 10, 2, 3, 4, // testing negative eigenvalue testcase
//                      2, 6, 7, 8,
//                      3, 7, 10, 11,
//                      4, 8, 11, 10};

	float a[DIM*DIM]= {0.503835  , 0.9355842 , 0.953972  , 0.33422518, 0.5711793 ,
		       0.8042752 , 0.980986  , 0.8583856 , 0.3060989 , 0.53269196,
		       0.06174436, 0.86542773, 0.84242594, 0.94639796, 0.7485421 ,
		       0.9355842 , 0.1101497 , 0.9864135 , 0.5014259 , 0.26593226,
		       0.3392466 , 0.5314261 , 0.9829542 , 0.07260937, 0.77934283,
		       0.78807455, 0.9267518 , 0.24562061, 0.8046551 , 0.04678277,
		       0.953972  , 0.9864135 , 0.7692478 , 0.56437206, 0.50158906,
		       0.48653182, 0.68068284, 0.79480606, 0.14180475, 0.05267152,
		       0.5543017 , 0.45673102, 0.710187  , 0.97818357, 0.38168466,
		       0.33422518, 0.5014259 , 0.56437206, 0.8472722 , 0.59632045,
		       0.39560658, 0.7819074 , 0.22753555, 0.5322465 , 0.48172098,
		       0.94241697, 0.7744959 , 0.95628566, 0.4069445 , 0.9093959 ,
		       0.5711793 , 0.26593226, 0.50158906, 0.59632045, 0.23741172,
		       0.05559118, 0.50143856, 0.11379261, 0.4574115 , 0.7300452 ,
		       0.13398051, 0.31015885, 0.91854584, 0.5510503 , 0.7983847 ,
		       0.8042752 , 0.3392466 , 0.48653182, 0.39560658, 0.05559118,
		       0.3130287 , 0.6202683 , 0.9407724 , 0.40616187, 0.72640836,
		       0.44199154, 0.6038176 , 0.38019446, 0.41183633, 0.27003142,
		       0.980986  , 0.5314261 , 0.68068284, 0.7819074 , 0.50143856,
		       0.6202683 , 0.35154924, 0.1437789 , 0.99511015, 0.2050128 ,
		       0.47240967, 0.12355002, 0.10807756, 0.20181388, 0.6046433 ,
		       0.8583856 , 0.9829542 , 0.79480606, 0.22753555, 0.11379261,
		       0.9407724 , 0.1437789 , 0.7058413 , 0.46841097, 0.5579322 ,
		       0.20421518, 0.9745761 , 0.9085669 , 0.33698344, 0.1567949 ,
		       0.3060989 , 0.07260937, 0.14180475, 0.5322465 , 0.4574115 ,
		       0.40616187, 0.99511015, 0.46841097, 0.6644227 , 0.8439967 ,
		       0.7348432 , 0.5056509 , 0.52478206, 0.04892552, 0.5096049 ,
		       0.53269196, 0.77934283, 0.05267152, 0.48172098, 0.7300452 ,
		       0.72640836, 0.2050128 , 0.5579322 , 0.8439967 , 0.4028809 ,
		       0.22280386, 0.20460154, 0.52577347, 0.14598744, 0.89472324,
		       0.06174436, 0.78807455, 0.5543017 , 0.94241697, 0.13398051,
		       0.44199154, 0.47240967, 0.20421518, 0.7348432 , 0.22280386,
		       0.21395533, 0.01715267, 0.48336193, 0.5570688 , 0.24414288,
		       0.86542773, 0.9267518 , 0.45673102, 0.7744959 , 0.31015885,
		       0.6038176 , 0.12355002, 0.9745761 , 0.5056509 , 0.20460154,
		       0.01715267, 0.13263962, 0.6930434 , 0.8779945 , 0.62739396,
		       0.84242594, 0.24562061, 0.710187  , 0.95628566, 0.91854584,
		       0.38019446, 0.10807756, 0.9085669 , 0.52478206, 0.52577347,
		       0.48336193, 0.6930434 , 0.11439001, 0.19757108, 0.92240316,
		       0.94639796, 0.8046551 , 0.97818357, 0.4069445 , 0.5510503 ,
		       0.41183633, 0.20181388, 0.33698344, 0.04892552, 0.14598744,
		       0.5570688 , 0.8779945 , 0.19757108, 0.3469131 , 0.14537218,
		       0.7485421 , 0.04678277, 0.38168466, 0.9093959 , 0.7983847 ,
		       0.27003142, 0.6046433 , 0.1567949 , 0.5096049 , 0.89472324,
		       0.24414288, 0.62739396, 0.92240316, 0.14537218, 0.5224271};

  float eig_vector[DIM*DIM], eig_value[DIM],sorted_eigenval[DIM],sorted_eigvec[DIM*DIM], comp;
  int index;

  float abs_diff = 0.0f, temp;

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
