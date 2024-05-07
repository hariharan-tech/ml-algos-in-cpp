//#include <stdio.h>
#include "SVD.hpp"
#include "SVD_top.h"
#include "sort.hpp"
//#include <iostream>

void svd_sort_select(stream_port &a_in, stream_port &sorted_eigvec,int &index_count, float &comp_rate)
{
	#pragma HLS INTERFACE mode=ap_ctrl_none port=return
	#pragma HLS INTERFACE mode=axis port=a_in
    #pragma HLS INTERFACE mode=axis port=sorted_eigvec
	#pragma HLS INTERFACE mode=s_axilite port=index_count
	#pragma HLS INTERFACE mode=s_axilite port=comp_rate

    int input_ind=0;
    float temp[DIM*DIM],eigvec[DIM*DIM],a[DIM*DIM], anext[DIM*DIM];
    float eigval[DIM];

//    float a_new[DIM*DIM];

    s_packet data_stream;

  DATA_READ: do{
	  data_stream=a_in.read();
	  a[input_ind] = data_stream.data;
//	  a_new[input_ind] = data_stream.data;
	  input_ind++;
  } while(!data_stream.last);


  //Initialize Eigen Vector matrix
  INIT_R0: for(int r=0; r<DIM ;r++)
   INIT_C0: for(int c=0;c<DIM; c++)
       eigvec[r*DIM+c] = c==r?1:0 ;

  int row,col;
  float sin_val, cos_val;
  ITER_LOOP: for(int i=0;i<DIM*(DIM-1);i++)
  {
      non_diag_max<DIM>(a,&row,&col);
      opt_rot_init<DIM>(row,col,a,&sin_val,&cos_val) ;
//      mult_A_Jt<DIM>(sin_val,cos_val,a,row,col,temp);
//      mult_J_A<DIM>(sin_val ,cos_val,temp,row,col,a);
      mult_JAJt<DIM>(sin_val,cos_val,a,row,col,anext);
      mult_J_A<DIM>(sin_val,cos_val,eigvec,row,col,temp);


//      std::cout<<std::endl<<row<<" - "<<col;
//      for(int i=0;i<DIM;i++){
//      		for(int j=0;j<DIM;j++)
//      			std::cout<<anext[i*DIM+j]<<" ";
////      			std::cout<<(a[i*DIM+j]==anext[i*DIM+j])<<" ";
//      		std::cout<<std::endl;
//      }
//
//      for(int i=0;i<DIM;i++){
//            		for(int j=0;j<DIM;j++)
//            			std::cout<<a[i*DIM+j]<<" ";
//      //      			std::cout<<(a[i*DIM+j]==anext[i*DIM+j])<<" ";
//            		std::cout<<std::endl;
//      }

//      std::cout<<std::endl;
      //Reassign Eigen vector Matrix

      ITER_I_EIGVEC_WRITE: for (int index=0;index < DIM*DIM; index++){
            #pragma HLS PIPELINE II=1
          eigvec[index]=temp[index];
          a[index] = anext[index];
      }

  }

  WRITE_LOOP_EIGVAL:for(int i=0;i<DIM;i++){
     #pragma HLS PIPELINE II=1
	  eigval[i] = hls::abs(a[i*DIM+i]);
//	  std::cout<<a[i*DIM+i]<<std::endl;
  }

  int sorted_index[DIM],index;
  float sorted_eig_buff[DIM], selected_eigenvec[L_MAX*DIM],comp;

  sort_desc<DIM>(eigval,sorted_eig_buff, sorted_index);
  energy_index_count<DIM>(sorted_eig_buff,index,comp);
  sort_eigenvector<DIM>(eigvec,sorted_index,index,selected_eigenvec);


  index_count=index;
  comp_rate=comp;
  WRITE_LOOP_SORTED_EIGENVAL_ROW:for(int i=0;i<DIM;i++){
	  WRITE_LOOP_SORTED_EIGENVAL_COL:for(int j=0;j<L_MAX;j++){
		  data_stream.data=selected_eigenvec[j*DIM+i];
		  data_stream.last= (i*L_MAX+j==(L_MAX*DIM)-1)?1:0;
		  sorted_eigvec.write(data_stream);
	  }
  }

}



