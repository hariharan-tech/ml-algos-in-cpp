#include<iostream>
#include "SVD_top.h"
#include<fstream>
#include<string>

//#define DIM 4
#define TEST_SAMPLES 10

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
	#include"input_vector_4x4.h"
	#include"output_vector_4x4.h"
	std::ofstream abs_loss_file("abs_loss"+std::to_string(DIM)+".txt");

  float eig_vector[DIM*DIM], eig_value[DIM],sorted_eigenval[DIM],sorted_eigvec[DIM*DIM], comp;
  int index;

  float abs_diff = 0.0f, temp;

  for(int test=0;test<TEST_SAMPLES;test++){
	  abs_diff = 0.0f;
	  std::cout<<test+1<<" iteration---"<<std::endl;
	  for(int count=DIM;count<DIM*DIM;count++){
		  std::cout<<count+1<<"\t--> ";
		  svd(input_vector[test],eig_value,eig_vector,count);

//	for (int i=0;i<DIM;i++){
//		std::cout<<eig_value[i]<<"\t";
//  	}
//   std::cout<<std::endl;
   sort_select(eig_vector,eig_value,sorted_eigenval,sorted_eigvec,index,comp);
//   std::cout<<"Required eigenvalue count: "<<index<<"\nCompression percentage: "<<comp<<std::endl;
//
	for (int i=0;i<DIM;i++){
		std::cout<<sorted_eigenval[i]<<"\t";
 	}
//
	std::cout<<std::endl;
//	for (int i=0;i<DIM;i++){
//			for(int j=0;j<DIM;j++)
//				std::cout<<eig_vector[i*DIM+j]<<"\t";
//			std::cout<<std::endl;
//		 }
//	std::cout<<std::endl;
//	for (int i=0;i<index;i++){
//		for(int j=0;j<DIM;j++)
//			std::cout<<sorted_eigvec[i*DIM+j]<<"\t";
//		std::cout<<std::endl;
//	 }
	abs_diff = 0.0f;
	for(int i=0;i<DIM;i++){
		temp = sorted_eigenval[i]-output_vector[test][i];
		abs_diff += (temp>=0)?(temp):(-temp);
	}
//	std::cout<<"Absolute difference in "<<test+1<<" sample is "<<abs_diff<<std::endl<<std::endl;
  }
	abs_loss_file<<abs_diff/(DIM*DIM - DIM)<<",";
  }
  abs_loss_file.close();
   return 0;
}
