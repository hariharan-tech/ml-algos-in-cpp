//#include <stdio.h>
#include "SVD.hpp"
#include "SVD_top.h"
#include "sort.hpp"
#include <iostream>

void pca(const float a_in[DIM*DIM],float sorted_eigvec[L_MAX*DIM],int &index_count, float &comp_rate)
{
	#pragma HLS INTERFACE mode=s_axilite port=return
	#pragma HLS INTERFACE mode=s_axilite port=a_in
	#pragma HLS INTERFACE mode=s_axilite port=sorted_eigvec
	#pragma HLS INTERFACE mode=s_axilite port=index_count
	#pragma HLS INTERFACE mode=s_axilite port=comp_rate


    float temp[DIM*DIM],eigvec[DIM*DIM],a[DIM*DIM];
    float eigval[DIM];
  READ_A_LOOP:for(int i=0;i<DIM*DIM;i++){
	  a[i] = a_in[i];
  }

  //Initialize Eigen Vector matrix
  INIT_R0: for(int r=0; r<DIM ;r++)
   INIT_C0: for(int c=0;c<DIM; c++)
       eigvec[r*DIM+c] = c==r?1:0 ;

  int row,col;
  float sin_val, cos_val;
  ITER_LOOP: for(int i=0;i<8*DIM;i++)
  {
      non_diag_max<DIM>(a,&row,&col);
      opt_rot_init<DIM>(row,col,a,&sin_val,&cos_val) ;
      mult_A_Jt<DIM>(sin_val,cos_val,a,row,col,temp);
      mult_J_A<DIM>(sin_val ,cos_val,temp,row,col,a);
      mult_J_A<DIM>(sin_val,cos_val,eigvec,row,col,temp);

      //Reassign Eigen vector Matrix

      ITER_I_EIGVEC_WRITE: for (int index=0;index < DIM*DIM; index++){
            #pragma HLS PIPELINE II=1
          eigvec[index]=temp[index];
      }

  }

  WRITE_LOOP_EIGVAL:for(int i=0;i<DIM;i++){
     #pragma HLS PIPELINE II=1
	  eigval[i] = hls::abs(a[i*DIM+i]);
  }

  int sorted_index[DIM],index;
  float sorted_eig_buff[DIM], selected_eigenvec[L_MAX*DIM],comp;

  sort_desc<DIM>(eigval,sorted_eig_buff, sorted_index);
  energy_index_count<DIM>(sorted_eig_buff,index,comp);
  sort_eigenvector<DIM>(eigvec,sorted_index,index,selected_eigenvec);

  index_count=index;
  comp_rate=comp;

  WRITE_LOOP_SORTED_EIGVAL:for(int i=0;i<L_MAX*DIM;i++){
     #pragma HLS PIPELINE II=1
	  sorted_eigvec[i] = selected_eigenvec[i];
  }

}



