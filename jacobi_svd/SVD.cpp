// This project takes in the 2 Dimension matrix in the form 1 D array.

#include <iostream>
#include <math.h>

#define DIM 5 // N X N Matrix dimension, this DIM is N
#define PRECISION 0.5f // Off diagonal sum threshold for stopping iteration

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
  - `rot_mat` is the Jacobi rotation matrix and its transpose is `rot_mat_t`
*/
template<int N>
void rot_init(const int i, const int j, const float a[],float rot_mat[],float rot_mat_t[])
{ 
   float aii, aij; // variable to store cos(theta) and sin(theta)
   float theta;
   theta=0.5*atan((2*a[i*N+j])/(a[i*N+i]-a[j*N+j])); // Calculating theta using (2aij/(aii-ajj))
   aii= cos(theta);
   aij= sin(theta);

  // Creating Identity matrix for J and J'
   for(int r=0; r<N ;r++)
     for(int c=0;c<N; c++)
     {
       rot_mat[r*N+c] = c==r?1:0 ; 
       rot_mat_t[r*N+c] = c==r?1:0 ; 
     }
  
  // Writing sin(theta) and cos(theta) at respective places
  // For matrix J
   rot_mat[i*N+i]=aii;
   rot_mat[i*N+j]=aij;
   rot_mat[j*N+i]=-aij;
   rot_mat[j*N+j]=aii;
  // For matrix J'
   rot_mat_t[i*N+i]=aii;
   rot_mat_t[i*N+j]=-aij;
   rot_mat_t[j*N+i]=aij;
   rot_mat_t[j*N+j]=aii;

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
    float max_val = 0; int max_r,max_c;
    for(int i=0;i<N;i++){
        for(int j=i+1;j<N;j++){
            if(abs(input_mat[N*i+j])>max_val){
                max_val = input_mat[N*i+j];
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


int main()
{
  // Declare variables (and initialize some)
  float a[DIM*DIM]= { 10, 2, 3, 4, 5,
                      2, 6, 7, 8, 2,
                      3, 7, 10, 11, 4,
                      4, 8, 11, 10, 1,
                      5, 2, 4, 1, 18};
  float rot_matrix[DIM*DIM],rot_matrix_t[DIM*DIM];
  float temp[DIM*DIM],eigvec[DIM*DIM];

  //Initialize Eigen Vector matrix (as Identity)
  for(int r=0; r<DIM ;r++)
   for(int c=0;c<DIM; c++)
       eigvec[r*DIM+c] = c==r?1:0 ;

  int row,col;
  float prec;

  // Find the initial non-diagonal values absolute sum
  non_diag_sum<DIM>(a,&prec);

  // Iterate until the precision is greater the set Threshold
  for(int i=0;prec>PRECISION;i++)
  {   
      non_diag_max<DIM>(a,&row,&col); // Find the location of non-diagonal absolute max value's row and col
      rot_init<DIM>(row,col,a,rot_matrix,rot_matrix_t); // Create the required J and J' matrix with row and col
      matrix_mul<DIM>(rot_matrix,a,temp); // Matrix multiply J and A
      matrix_mul<DIM>(temp,rot_matrix_t,a); // Computing JAJ' now

      // The final eigenvector is a product of rotation matrix at each iteration
      matrix_mul<DIM>(rot_matrix,eigvec,temp); // Multiplying Ji with J to find eigenvector

      //Reassign Eigen vector Matrix
      for (int index=0;index < DIM*DIM; index++)
          eigvec[index]=temp[index];

      // Find the non-diagonal absolute sum
      non_diag_sum<DIM>(a,&prec);
      std::cout<<i<<"\t"<<prec<<"\t\t\t\t";
      
      // Printing eigenvalues for each iteration
      for (int k=0;k<DIM;k++)
      {
          std::cout<<a[k*DIM+k]<<" ";
      }
      std::cout<<std::endl;
  }
  // Printing final eigenvectors
  std::cout<<std::endl;
  for (int i=0; i<DIM; i++)
  {
    for (int j=0;j<DIM;j++)
      std::cout<<eigvec[i*DIM+j]<<" ";
    std::cout<<std::endl;
  }
}