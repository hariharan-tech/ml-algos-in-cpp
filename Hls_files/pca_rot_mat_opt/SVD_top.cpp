//#include <stdio.h>
#include "SVD.hpp"
#include "SVD_top.h"

void svd(const float a_in[DIM*DIM],float eigval_op[DIM],float eigvec_op[DIM*DIM])
{
	#pragma HLS INTERFACE mode=s_axilite port=return
	#pragma HLS INTERFACE mode=s_axilite port=a_in
	#pragma HLS INTERFACE mode=s_axilite port=eigval_op
	#pragma HLS INTERFACE mode=s_axilite port=eigvec_op
    float temp[DIM*DIM],eigvec[DIM*DIM],a[DIM*DIM];
  READ_A_LOOP:for(int i=0;i<DIM*DIM;i++){
	  a[i] = a_in[i];
  }

  //Initialize Eigen Vector matrix
  INIT_R0: for(int r=0; r<DIM ;r++)
   INIT_C0: for(int c=0;c<DIM; c++)
       eigvec[r*DIM+c] = c==r?1:0 ;

  int row,col;
//  float prec;
//  prec=std::numeric_limits<float>::max();
  float sin_val, cos_val;
  ITER_LOOP: for(int i=0;i<4*DIM;i++)
  {
      non_diag_max<DIM>(a,&row,&col);
      opt_rot_init<DIM>(row,col,a,&sin_val,&cos_val) ;
      mult_A_Jt<DIM>(sin_val,cos_val,a,row,col,temp);
      mult_J_A<DIM>(sin_val ,cos_val,temp,row,col,a);
      mult_J_A<DIM>(sin_val,cos_val,eigvec,row,col,temp);

      //Reassign Eigen vector Matrix

      ITER_I_EIGVEC_WRITE: for (int index=0;index < DIM*DIM; index++){
//          #pragma HLS UNROLL
            #pragma HLS PIPELINE II=1
          eigvec[index]=temp[index];
      }

  }
  WRITE_LOOP_EIGVEC:for(int i=0;i<DIM*DIM;i++){
      #pragma HLS PIPELINE II=1
	  eigvec_op[i] = eigvec[i];
  }
  WRITE_LOOP_EIGVAL:for(int i=0;i<DIM;i++){
	  eigval_op[i] = hls::abs(a[i*DIM+i]);
  }
}



