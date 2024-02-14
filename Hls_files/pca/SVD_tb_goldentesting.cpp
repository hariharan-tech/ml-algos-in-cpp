#include<iostream>
#include "SVD_top.h"
#include<fstream>
#include<string>

//#define DIM 4
#define TEST_SAMPLES 20
#define START_ITER DIM
#define END_ITER DIM*DIM

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
	#include"input_vector_50x50.h"
	#include"output_vector_50x50.h"
	std::ofstream abs_loss_file("abs_loss"+std::to_string(DIM)+".txt");

  float eig_vector[DIM*DIM], eig_value[DIM],sorted_eigenval[DIM],sorted_eigvec[DIM*DIM], comp;
  int index;

  float abs_diff = 0.0f, temp;

  for(int count=START_ITER;count<END_ITER-1;count++)
	  abs_loss_file<<std::to_string(count)<<",";
  abs_loss_file<<std::to_string(END_ITER)<<"\n";
  for(int test=0;test<TEST_SAMPLES;test++){ // Each test sample
	  std::cout<<test+1<<" iteration---"<<std::endl;
	  for(int count=START_ITER;count<END_ITER;count++){ // Different number of iterations
//		  std::cout<<count+1<<"\t--> ";
		  svd(input_vector[test],eig_value,eig_vector,count);
		  sort_select(eig_vector,eig_value,sorted_eigenval,sorted_eigvec,index,comp);
//		  for (int i=0;i<DIM;i++){
//			std::cout<<sorted_eigenval[i]<<"\t";
//		  }
//		  std::cout<<std::endl;
		  abs_diff = 0.0f;
		  for(int i=0;i<DIM;i++){
			temp = sorted_eigenval[i]-output_vector[test][i];
			abs_diff += (temp>=0)?(temp):(-temp);
		  }
		  abs_loss_file<<abs_diff;
		  if(count!=END_ITER-1) abs_loss_file<<",";
		  else abs_loss_file<<std::endl;
	  }
    }
  abs_loss_file.close();
  return 0;
}
