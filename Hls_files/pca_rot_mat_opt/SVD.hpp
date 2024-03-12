#include "hls_math.h"

template <int N>
void matrix_mul(const float a_in[N*N],const float b_in[N*N], float c_out[N*N])
//void matrix_mul(const float a[N*N],const float b[N*N], float c[N*N])
{
    #pragma HLS INLINE off
	float a[N*N],b[N*N];
    #pragma HLS ARRAY_RESHAPE variable=a factor=N type=cyclic
    #pragma HLS ARRAY_RESHAPE variable=b factor=N type=block
	COPY_A_B: for(int i=0; i<N*N; i++){
		a[i]=a_in[i];
		b[i]=b_in[i];
	}

 //    Matrix multiplication of 2 NxN matrices
   float sum;
   MATMUL_R: for (int i=0;i<N;i++)
      MATMUL_C: for (int j=0; j<N;j++)
      {
         sum=0;
         MATMUL_ADD: for (int k=0;k<N;k++)
         {
//           #pragma HLS PIPELINE II=1
            sum+=a[N*i+k]*b[k*N+j];
         }
         c_out[i*N+j]=sum;
      }

//	MATMUL_R: for(int i=0;i<N;i++){
//	  float sum[N];
//	  MATMUL_ADD: for (int k=0;k<N;k++)
//	  {
//	    MATMUL_C: for (int j=0; j<N;j++)
//	    {
//	      #pragma HLS PIPELINE II=1
//	      float temp=(k==0)? static_cast< float > (0): sum[j];
//	      sum[j]=temp+a[N*i+k]*b[k*N+j];
//	      #pragma HLS DEPENDENCE false variable=sum
//	    }
//	  }
//	 WRITE_ROW_SUM:for(int j=0;j<N;j++){
//	   #pragma HLS PIPELINE II=1
//	         c[i*N+j]=sum[j];
//	 }
//
//	}
}

// Computes JA given A and sin, cos values
template<int N>
void mult_A_Jt(float const sin_val, float const cos_val, float const a[N*N], int const p, int const q, float a_jt[N*N]){
  //#pragma HLS INLINE off
  A_Jt_RLOOP:for(int i=0;i<N;i++){
//	#pragma HLS PIPELINE II=1
    A_Jt_CLOOP:for(int j=0;j<N;j++){
      a_jt[i*N+j] = (j==p||j==q)?((j==p)?(a[i*N+p]*cos_val + a[i*N+q]*sin_val):(-a[i*N+p]*sin_val + a[i*N+q]*cos_val)):(a[i*N+j]);
    }
  }
}

// Computes JAJ' given JA and sin, cos values
template<int N>
void mult_J_AJt(float const sin_val, float const cos_val, float const a[N*N], int const p, int const q, float j_a_jt[N*N]){
  //#pragma HLS INLINE off
  J_A_Jt_RLOOP:for(int i=0;i<N;i++){
//    #pragma HLS PIPELINE II=1
    J_A_Jt_CLOOP:for(int j=0;j<N;j++){
      j_a_jt[i*N+j] = (i==p||i==q)?((i==p)?(a[p*N+j]*cos_val + a[q*N+j]*sin_val):(-a[p*N+j]*sin_val + a[q*N+j]*cos_val)):(a[i*N+j]);
    }
  }
}

// Optimized Rot INIT function
template<int N>
void opt_rot_init(const int i, const int j, const float a[N*N], float rot_mat[N*N]) //, float *sin_value, float *cos_value)
{
   float aii, aij; // variable to store cos(theta) and sin(theta)
   float theta;

   theta=0.5*hls::atan((2*a[i*N+j])/(a[i*N+i]-a[j*N+j])); // Calculating theta using (2aij/(aii-ajj))
   aii= hls::cosf(theta);
   aij= hls::sinf(theta);

  // Creating Identity matrix for J and J'
   ROT_INIT_RLOOP:for(int r=0; r<N ;r++)
     ROT_INIT_CLOOP:for(int c=0;c<N; c++)
     {
       #pragma HLS PIPELINE II = 1
       rot_mat[r*N+c] = c==r?1:0;
     }

  // Writing sin(theta) and cos(theta) at respective places
  // For matrix J
   rot_mat[i*N+i]=aii;
   rot_mat[i*N+j]=aij;
   rot_mat[j*N+i]=-aij;
   rot_mat[j*N+j]=aii;

//   *cos_value = aii;
//   *sin_value = aij;

}

//template<int N>
//void rot_init(const int i, const int j, const float a[N*N],float rot_mat[N*N],float rot_mat_t[N*N])
//{
//   // To calculate the rotation Matrix J and J transpose
//   float aii, aij;
//   float theta;
//   theta=0.5*hls::atanf((2*a[i*N+j])/(a[i*N+i]-a[j*N+j]));
//   aii= hls::cosf(theta);
//   aij= hls::sinf(theta);
//
//   ROT_INIT_R: for(int r=0; r<N ;r++)
//     ROT_INIT_C: for(int c=0;c<N; c++)
//     {
//	   #pragma HLS PIPELINE II=1
//       rot_mat[r*N+c] = c==r?1:0 ;
//       rot_mat_t[r*N+c] = c==r?1:0 ;
//     }
//
//   rot_mat[i*N+i]=aii;
//   rot_mat[i*N+j]=aij;
//   rot_mat[j*N+i]=-aij;
//   rot_mat[j*N+j]=aii;
//
//   rot_mat_t[i*N+i]=aii;
//   rot_mat_t[i*N+j]=-aij;
//   rot_mat_t[j*N+i]=aij;
//   rot_mat_t[j*N+j]=aii;
//
//}

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
 // #pragma HLS INLINE off
  float temp=0;
  NON_DIAG_SUM_R:for(int i=0;i<N;i++){
    NON_DIAG_SUM_C:for(int j=0;j<N;j++){
//#pragma HLS UNROLL factor=N
      temp += (i>=j)?0:hls::fabs(input_mat[i*N+j]);
    }
  }
  *sum = 2*temp;
}
