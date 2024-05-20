// This project takes in the 2 Dimension matrix in the form 1 D array.

#include <iostream>
#include <math.h>

#define DIM 15 // N X N Matrix dimension, this DIM is N
#define TEST_SAMPLES 1
#define PRECISION DIM*(DIM-1)*0.1f // Off diagonal sum threshold for stopping iteration

/*Matrix Multiplication of 2 matrices of dimension N X N (Where N is specified with template)
  #### Inputs
  - `a` and `b` are the input N x N matrix
  #### Outputs
  - `c` is the product N x N matrix
*/
template <int N>
void matrix_mul(const float a[],const float b[], float c[])
{
   float sum; // Sum variable
   for (int i=0;i<N;i++)
      for (int j=0; j<N;j++)
      {
         sum=0;
         for (int k=0;k<N;k++)
         {
            sum+=a[N*i+k]*b[k*N+j];
         }
         c[i*N+j]=sum;
      }
      
}

/* Generates J (Jacobi matrix) and J' for a given
  #### Inputs
  - `i` and `j` are the values for i_th row and j_th column (indicates the location of maximum non diagonal element)
  - `a` matrix is the input matrix
  #### Outputs
  - `rot_mat` is the Jacobi rotation matrix
*/
template<int N>
void rot_init(const int i, const int j, const float a[], float rot_mat[], float *sin_value, float *cos_value)
{ 
   float aii, aij; // variable to store cos(theta) and sin(theta)
   float theta;

   theta=0.5*atan((2*a[i*N+j])/(a[i*N+i]-a[j*N+j])); // Calculating theta using (2aij/(aii-ajj))
   std::cout<<theta<<"\t";
   aii= cos(theta);
   aij= sin(theta);

  // Creating Identity matrix for J and J'
   for(int r=0; r<N ;r++)
     for(int c=0;c<N; c++)
     {
       rot_mat[r*N+c] = c==r?1:0;
     }
  
  // Writing sin(theta) and cos(theta) at respective places
  // For matrix J
   rot_mat[i*N+i]=aii;
   rot_mat[i*N+j]=aij;
   rot_mat[j*N+i]=-aij;
   rot_mat[j*N+j]=aii;

   *cos_value = aii;
   *sin_value = aij;

}

/*Find the row and column of the absolute maximum non-diagonal value in the matrix
  #### Inputs
  - `input_mat` is the 1D N*N matrix
  #### Outputs
  - `r` and `c` are the row and column value respectively
*/
template <int N>
void non_diag_max(float const input_mat[], int *r, int *c)
{
    float max_val = 0,temp; int max_r,max_c;
    for(int i=0;i<N;i++){
        for(int j=i+1;j<N;j++){
            temp = abs(input_mat[i*N+j]);
            if(temp>max_val){
                max_val = temp;
                max_r = i; max_c = j;
            }
        }
    }
    *r = max_r; *c = max_c;
}

/*Find the sum of absolute of non-diagonal elements in a matrix
  #### Inputs
  - `input_mat` is the 1D N*N matrix
  #### Outputs
  - `sum` is the absolute sum
*/
template<int N>
void non_diag_sum(float const input_mat[], float *sum){
  float temp=0;
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++)
      temp += (i==j)?0:abs(input_mat[i*N+j]);
  }
  *sum = temp;
}


template<int N>
void non_diag_sum_opt(float const input_mat[], float *sum){
  float temp=0;
  for(int i=0;i<N;i++){
    for(int j=i+1;j<N;j++)
      temp += (i==j)?0:abs(input_mat[i*N+j]);
  }
  *sum = temp;
}

template<int N>
void mult_A_Jt(float const sin_val, float const cos_val, float const a[], int const p, int const q, float a_jt[]){
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      a_jt[i*N+j] = (j==p||j==q)?((j==p)?(a[i*N+p]*cos_val + a[i*N+q]*sin_val):(-a[i*N+p]*sin_val + a[i*N+q]*cos_val)):(a[i*N+j]);
      // switch(j){
      //   case p:{
      //     a_jt[i*N+j] = a[i*N+p]*cos_val + a[i*N+q]*sin_val;
      //     break;
      //   }
      //   case q:{
      //     a_jt[i*N+j] = -a[i*N+p]*sin_val + a[i*N+q]*cos_val;
      //     break;
      //   }
      //   default:{
      //     a_jt[i*N+j] = a[i*N+j];
      //     break;
      //   }
      // }
    }
  }
}

template<int N>
void mult_J_AJt(float const sin_val, float const cos_val, float const a[], int const p, int const q, float j_a_jt[]){
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      j_a_jt[i*N+j] = (i==p||i==q)?((i==p)?(a[p*N+j]*cos_val + a[q*N+j]*sin_val):(-a[p*N+j]*sin_val + a[q*N+j]*cos_val)):(a[i*N+j]);
      // switch(i){
      //   case p:{
      //     j_a_jt[i*N+j] = a[p*N+j]*cos_val + a[q*N+j]*sin_val;
      //     break;
      //   }
      //   case q:{
      //     j_a_jt[i*N+j] = -a[p*N+j]*sin_val + a[q*N+j]*cos_val;
      //     break;
      //   }
      //   default:{
      //     j_a_jt[i*N+j] = a[i*N+j];
      //     break;
      //   }
      // }
    }
  }
}

#include"input_vector_15x15.h"
#include"output_vector_15x15.h"

int main()
{
  // Declare variables (and initialize some)
  // float a[DIM*DIM] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
  //       2, 11, 12, 13, 14, 15, 16, 17, 18, 19,
  //       3, 12, 20, 21, 22, 23, 24, 25, 26, 27,
  //       4, 13, 21, 28, 29, 30, 31, 32, 33, 34,
  //       5, 14, 22, 29, 35, 36, 37, 38, 39, 40,
  //       6, 15, 23, 30, 36, 41, 42, 43, 44, 45,
  //       7, 16, 24, 31, 37, 42, 46, 47, 48, 49,
  //       8, 17, 25, 32, 38, 43, 47, 50, 51, 52,
  //       9, 18, 26, 33, 39, 44, 48, 51, 53, 54,
  //       10, 19, 27, 34, 40, 45, 49, 52, 54, 55
  //   };

  float a[TEST_SAMPLES][DIM*DIM];
  float rot_matrix[DIM*DIM];
  float sin_val, cos_val;
  float temp[DIM*DIM],eigvec[DIM*DIM];

  //Initialize Eigen Vector matrix (as Identity)
  for(int r=0; r<DIM ;r++)
   for(int c=0;c<DIM; c++)
       eigvec[r*DIM+c] = c==r?1:0 ;

  int row,col;
  float prec;

  for(int test_sample=0;test_sample<TEST_SAMPLES;test_sample++){
    for(int i=0;i<DIM*DIM;i++){
      a[test_sample][i] = input_vector[test_sample][i];
    }
  // Find the initial non-diagonal values absolute sum
  non_diag_sum<DIM>(a[test_sample],&prec);
  // non_diag_sum_opt<DIM>(a,&prec_opt);

  // Iterate until the precision is greater the set Threshold
  for(int i=0;prec>PRECISION;i++)
  // for(int i=0;i<DIM*4;i++)
  {   
      non_diag_max<DIM>(a[test_sample],&row,&col); // Find the location of non-diagonal absolute max value's row and col
    //   for(int r=0;r<DIM;r++)
    // {for(int c=0;c<DIM;c++)
    //   std::cout<<a[r*DIM+c]<<"  ";
    // std::cout<<std::endl;}
      
    //   rot_init<DIM>(row,col,a[test_sample],rot_matrix,rot_matrix_t); // Create the required J and J' matrix with row and col
      // matrix_mul<DIM>(rot_matrix,a[test_sample],temp); // Matrix multiply J and A
      // matrix_mul<DIM>(temp,rot_matrix_t,a[test_sample]); // Computing A_i+1 = J*A_i*J' now
      
      // Optimized JAJ' computation!
      rot_init<DIM>(row,col,a[test_sample],rot_matrix,&sin_val,&cos_val);
      mult_A_Jt<DIM>(sin_val,cos_val,a[test_sample],row,col,temp);
      mult_J_AJt<DIM>(sin_val,cos_val,temp,row,col,a[test_sample]);

      // The final eigenvector is a product of rotation matrix at each iteration
      matrix_mul<DIM>(rot_matrix,eigvec,temp); // Multiplying Ji with J to find eigenvector

      //Reassign Eigen vector Matrix
      for (int index=0;index < DIM*DIM; index++)
          eigvec[index]=temp[index];

      // Find the non-diagonal absolute sum
      non_diag_sum<DIM>(a[test_sample],&prec);
      // non_diag_sum_opt<DIM>(a,&prec_opt);
      std::cout<<i<<"\t"<<prec<<"\t\t\t\t";
      
      // Printing eigenvalues for each iteration
      for (int k=0;k<DIM;k++)
      // {  for(int j=0;j<DIM;j++)
          std::cout<<a[test_sample][k*DIM+k]<<" ";
          // std::cout<<std::endl;
      // }
      std::cout<<std::endl;
  }
  // Printing final eigenvectors
  std::cout<<std::endl;
  for (int i=0; i<DIM; i++)
  {
    for (int j=0;j<DIM;j++)
      std::cout<<eigvec[i*DIM+j]<<" ";
    std::cout<<std::endl<<std::endl;
  }
  }
}