#include <iostream>
#include <math.h>

#define DIM 4
#define PRECISION 0.5f

template <int N>
void matrix_mul(const float a[],const float b[], float c[])
{
   // Matrix multiplication of 2 NxN matrices 
   float sum;
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

template<int N >
void rot_init(const int i, const int j, const float a[],float rot_mat[],float rot_mat_t[])
{ 
   // To calculate the rotation Matrix J and J transpose
   float aii, aij;
   float theta;
   theta=0.5*atan((2*a[i*N+j])/(a[i*N+i]-a[j*N+j]));
   aii= cos(theta);
   aij= sin(theta);

   for(int r=0; r<N ;r++)
     for(int c=0;c<N; c++)
     {
       rot_mat[r*N+c] = c==r?1:0 ; 
       rot_mat_t[r*N+c] = c==r?1:0 ; 
     }
    
   rot_mat[i*N+i]=aii;
   rot_mat[i*N+j]=aij;
   rot_mat[j*N+i]=-aij;
   rot_mat[j*N+j]=aii;

   rot_mat_t[i*N+i]=aii;
   rot_mat_t[i*N+j]=-aij;
   rot_mat_t[j*N+i]=aij;
   rot_mat_t[j*N+j]=aii;

}

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
  float a[DIM*DIM]= {9,2,3,4,2,8,6,7,3,6,16,9,4,7,9,10};
  float rot_matrix[DIM*DIM],rot_matrix_t[DIM*DIM];
  float temp[DIM*DIM],eigvec[DIM*DIM];

  //Initialize Eigen Vector matrix
  for(int r=0; r<DIM ;r++)
   for(int c=0;c<DIM; c++)
       eigvec[r*DIM+c] = c==r?1:0 ;

  int row,col;
  float prec;
  non_diag_sum<DIM>(a,&prec);
  for(int i=0;prec>PRECISION;i++)
  {
      non_diag_max<DIM>(a,&row,&col);
      rot_init<DIM>(row,col,a,rot_matrix,rot_matrix_t);
      matrix_mul<DIM>(rot_matrix,a,temp);
      matrix_mul<DIM>(temp,rot_matrix_t,a);

      matrix_mul<DIM>(rot_matrix,eigvec,temp);

      //Reassign Eigen vector Matrix
      
      for (int index=0;index < DIM*DIM; index++)
          eigvec[index]=temp[index];

      non_diag_sum<DIM>(a,&prec);
      std::cout<<i<<"\t"<<prec<<"\t\t\t\t";
      
      for (int k=0;k<DIM;k++)
      {
          std::cout<<a[k*DIM+k]<<" ";
      }
      std::cout<<std::endl;
  }
  std::cout<<std::endl;
  for (int i=0; i<DIM; i++)
  {
    for (int j=0;j<DIM;j++)
      std::cout<<eigvec[i*DIM+j]<<" ";
    std::cout<<std::endl;
  }
}