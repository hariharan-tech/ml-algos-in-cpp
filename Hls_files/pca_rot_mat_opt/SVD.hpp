#include "hls_math.h"


// Computes JA given A and sin, cos values
template<int N>
void mult_A_Jt(float const sin_val, float const cos_val, float const a[N*N], int const p, int const q, float a_jt[N*N]){
  #pragma HLS INLINE off
  A_Jt_RLOOP:for(int i=0;i<N;i++){
    A_Jt_CLOOP:for(int j=0;j<N;j++){
         #pragma HLS PIPELINE II=1
//      a_jt[i*N+j] = (j==p||j==q)?((j==p)?(a[i*N+p]*cos_val + a[i*N+q]*sin_val):(-a[i*N+p]*sin_val + a[i*N+q]*cos_val)):(a[i*N+j]);
        a_jt[i*N+j]= (j==p)? a[i*N+p]*cos_val+a[i*N+q]*sin_val : (j==q)?  a[i*N+p]*-1*sin_val+a[i*N+q]*cos_val : a[i*N+j];
    }
  }
}

// Computes JAJ' given JA and sin, cos values
template<int N>
void mult_J_A(float const sin_val, float const cos_val, float const a[N*N], int const p, int const q, float j_a[N*N]){
  #pragma HLS INLINE off
  J_A_RLOOP:for(int i=0;i<N;i++){
    J_A_CLOOP:for(int j=0;j<N;j++){
        #pragma HLS PIPELINE II=1
//      j_a[i*N+j] = (i==p||i==q)?((i==p)?(a[p*N+j]*cos_val + a[q*N+j]*sin_val):(-a[p*N+j]*sin_val + a[q*N+j]*cos_val)):(a[i*N+j]);
    	j_a[i*N+j]= (i==p)? a[p*N+j]*cos_val+a[q*N+j]*sin_val : (i==q)?  a[p*N+j]*-1*sin_val+a[q*N+j]*cos_val : a[i*N+j];
    }
  }
}


// Computes JAJ' given A and sin, cos values
template<int N>
void mult_JAJt(float const sin_val, float const cos_val, float const a[N*N], int const p, int const q, float j_a_jt[N*N]){
	#pragma HLS INLINE
	float sin2val = sin_val*sin_val, cos2val = cos_val*cos_val, sincos = cos_val*sin_val;
	JAJt_RLOOP:for(int i=0;i<N;i++){
		JAJt_CLOOP:for(int j=0;j<N;j++){
            #pragma HLS loop_flatten
            #pragma HLS PIPELINE II=1
			if((!(i==p|| i==q) && j==p)){
				j_a_jt[i*N+j] = cos_val*a[i*N+p] + sin_val*a[i*N+q];
			}
			else if((!(j==p|| j==q) && i==p)){
				j_a_jt[i*N+j] = cos_val*a[j*N+p] + sin_val*a[j*N+q];
			}
			else if((!(i==p|| i==q) && j==q)){
				j_a_jt[i*N+j] = -sin_val*a[i*N+p] + cos_val*a[i*N+q];
			}
			else if((!(j==p|| j==q) && i==q)){
				j_a_jt[i*N+j] = -sin_val*a[j*N+p] + cos_val*a[j*N+q];
			}
			else if(i==p && j==p){
				j_a_jt[i*N+j] = cos2val*a[p*N+p] + 2*sincos*a[p*N+q] + sin2val*a[q*N+q];
			}
			else if(i==q && j==q){
				j_a_jt[i*N+j] = sin2val*a[p*N+p] - 2*sincos*a[p*N+q] + cos2val*a[q*N+q];
			}
			else if((i==p && j==q) || (i==q && j==p)){
				j_a_jt[i*N+j] = sincos*(a[q*N+q] - a[p*N+p]) + (cos2val - sin2val)*a[p*N+q];
			}
			else{
				j_a_jt[i*N+j] = a[i*N+j];
			}
//			std::cout<<flag<<" ";
		}
//		std::cout<<std::endl;
	}
}


// Optimized Rot INIT function
template<int N>
void opt_rot_init(const int i, const int j, const float a[N*N], float *sin_value, float *cos_value)
{
   #pragma HLS INLINE off
   float aii, aij; // variable to store cos(theta) and sin(theta)
   float theta;

   theta=0.5*hls::atan((2*a[i*N+j])/(a[i*N+i]-a[j*N+j])); // Calculating theta using (2aij/(aii-ajj))
   aii= hls::cosf(theta);
   aij= hls::sinf(theta);

   *cos_value = aii;
   *sin_value = aij;

}

template <int N>
void non_diag_max(float const input_mat[N*N], int *r, int *c)
{
    #pragma HLS INLINE off
    float max_val = 0,temp; int max_r=0,max_c=0;
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


