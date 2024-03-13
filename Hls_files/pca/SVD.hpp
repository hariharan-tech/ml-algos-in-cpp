#include "hls_math.h"

template <int N>
void matrix_mul(const float a[N*N],const float b[N*N], float c[N*N])
{
//	#pragma HLS ARRAY_RESHAPE variable=a type=cyclic factor=N
//	#pragma HLS ARRAY_RESHAPE variable=b type=block factor=N
//   // Matrix multiplication of 2 NxN matrices
//   #pragma HLS inline off
   float sum;

   MATMUL_R: for (int i=0;i<N;i++)
      MATMUL_C: for (int j=0; j<N;j++)
      {
         sum=0;
         MATMUL_ADD: for (int k=0;k<N;k++)
         {
        	 //#pragma HLS PIPELINE II=1
            sum+=a[N*i+k]*b[k*N+j];
         }
         c[i*N+j]=sum;
      }
      
}

template<int N >
void rot_init(const int i, const int j, const float a[N*N],float rot_mat[N*N],float rot_mat_t[N*N])
{ 
   // To calculate the rotation Matrix J and J transpose
   float aii, aij;
   float theta;
   theta=0.5*hls::atanf((2*a[i*N+j])/(a[i*N+i]-a[j*N+j]));
   aii= hls::cosf(theta);
   aij= hls::sinf(theta);

   ROT_INIT_R: for(int r=0; r<N ;r++)
     ROT_INIT_C: for(int c=0;c<N; c++)
     {
	   #pragma HLS PIPELINE II=1
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
void non_diag_max(float const input_mat[N*N], int *r, int *c)
{
#pragma HLS INLINE off
    float max_val = 0,temp; int max_r=0,max_c=0;
//    unsigned char flag;
    MAX_R: for(int i=0;i<N;i++){
//        MAX_C: for(int j=i+1;j<N;j++){
//        	temp = hls::fabs(input_mat[i*N+j]);
//			if(temp>max_val){
//				max_val = temp;
//				max_r = i; max_c = j;
//			}
		MAX_C: for(int j=0;j<N;j++){
			#pragma HLS PIPELINE II=1
        	if(i<=j) break;
        	else{
				temp = hls::fabs(input_mat[i*N+j]);
				if(temp>max_val){
					max_val = temp;
					max_r = i; max_c = j;
				}
        	}
        }
    }
    *r = max_r; *c = max_c;
}

template<int N>
void non_diag_sum(float const input_mat[N*N], float *sum){
  float temp=0;
  NON_DIAG_SUM_R:for(int i=0;i<N;i++){
    NON_DIAG_SUM_C:for(int j=0;j<N;j++){
//      #pragma HLS UNROLL
      temp += (i>=j)?0:hls::fabs(input_mat[i*N+j]);
    }
  }
  *sum = 2*temp;
}
