//#include <stdio.h>
#include "SVD.hpp"
#include "SVD_top.h"
#include "sort.hpp"
#include <iostream>

void pca(mystream &a_in, mystream &sorted_eigvec,int &index_count, float &comp_rate)
{
	#pragma HLS INTERFACE mode=ap_ctrl_none port=return
	#pragma HLS INTERFACE mode=axis port=a_in
    #pragma HLS INTERFACE mode=axis port=sorted_eigvec
	#pragma HLS INTERFACE mode=s_axilite port=index_count
	#pragma HLS INTERFACE mode=s_axilite port=comp_rate

    int input_ind=0;
    float temp[DIM*DIM],eigvec[DIM*DIM],a[DIM*DIM];
    float eigval[DIM];

    stream_inp in_data;

  do{
	  in_data=a_in.read();
	  a[input_ind] = in_data.data;
	  input_ind++;
  } while(!in_data.last);

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
  stream_inp out_data;
  WRITE_LOOP_SORTED_EIGVAL:for(int i=0;i<L_MAX*DIM;i++){
     #pragma HLS PIPELINE II=1
	  out_data.data=selected_eigenvec[i];
	  out_data.last= (i==(L_MAX*DIM)-1 )?1:0;
	  sorted_eigvec.write(out_data);
  }

}



