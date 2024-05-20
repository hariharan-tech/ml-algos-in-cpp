// This project takes in the 2 Dimension matrix in the form 1 D array.

#include <iostream>
#include <math.h>

#define DIM 15 // N X N Matrix dimension, this DIM is N
#define PRECISION 0.1f // Off diagonal sum threshold for stopping iteration

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
   std::cout<<theta<<"\t";
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

int main()
{
  // Declare variables (and initialize some)
  float a[DIM*DIM] = {0.503835  , 0.9355842 , 0.953972  , 0.33422518, 0.5711793 ,
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
  // non_diag_sum_opt<DIM>(a,&prec_opt);

  // Iterate until the precision is greater the set Threshold
  for(int i=0;prec>PRECISION;i++)
  // for(int i=0;i<DIM*4;i++)
  {   
      non_diag_max<DIM>(a,&row,&col); // Find the location of non-diagonal absolute max value's row and col
    //   for(int r=0;r<DIM;r++)
    // {for(int c=0;c<DIM;c++)
    //   std::cout<<a[r*DIM+c]<<"  ";
    // std::cout<<std::endl;}
      
      rot_init<DIM>(row,col,a,rot_matrix,rot_matrix_t); // Create the required J and J' matrix with row and col
      matrix_mul<DIM>(rot_matrix,a,temp); // Matrix multiply J and A
      matrix_mul<DIM>(temp,rot_matrix_t,a); // Computing A_i+1 = J*A_i*J' now

      // The final eigenvector is a product of rotation matrix at each iteration
      matrix_mul<DIM>(rot_matrix,eigvec,temp); // Multiplying Ji with J to find eigenvector

      //Reassign Eigen vector Matrix
      for (int index=0;index < DIM*DIM; index++)
          eigvec[index]=temp[index];

      // Find the non-diagonal absolute sum
      non_diag_sum<DIM>(a,&prec);
      // non_diag_sum_opt<DIM>(a,&prec_opt);
      std::cout<<i<<"\t"<<prec<<"\t\t\t\t";
      
      // Printing eigenvalues for each iteration
      for (int k=0;k<DIM;k++)
      // {  for(int j=0;j<DIM;j++)
          std::cout<<a[k*DIM+k]<<" ";
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