#include "projection_unit.h"

void projection(stream_port &data,stream_port &eig_vec, stream_port &result, int* status){

	#pragma HLS INTERFACE mode=ap_ctrl_none port=return
	#pragma HLS INTERFACE mode=axis port=data
	#pragma HLS INTERFACE mode=axis port=eig_vec
	#pragma HLS INTERFACE mode=axis port=result
	#pragma HLS INTERFACE mode=s_axilite port=status

	float data_in[DATA_SIZE*BANDS],eig_vec_in[BANDS*L_MAX],result_in[DATA_SIZE*L_MAX];
	int index=0;
	s_packet read_stream;
	do{
       read_stream=data.read();
       data_in[index]=read_stream.data;
       index++;
	}while(!read_stream.last);

	index=0;

	do{
	    read_stream=eig_vec.read();
	    eig_vec_in[index]=read_stream.data;
	    index++;
	}while(!read_stream.last);

//	status = 2;

//	#pragma HLS ARRAY_PARTITION variable=data_in type=cyclic factor=BANDS
	#pragma HLS ARRAY_PARTITION variable=eig_vec_in type=block factor=BANDS

	row: for (int i=0; i<DATA_SIZE; i++){
		col: for (int j=0;j<L_MAX;j++){
			 float temp=0;
             #pragma HLS PIPELINE II=1
	         prod: for (int  k=0;k<BANDS;k++){
				temp+=data_in[i*BANDS+k]*eig_vec_in[k*L_MAX+j];
			}
	         result_in[i*L_MAX+j] = temp;
		}
	}

	   *status = 1;

		for(int i=0;i<DATA_SIZE*L_MAX;i++){
	         read_stream.data=result_in[i];
	         read_stream.last=(i==DATA_SIZE*L_MAX-1)?1:0;
	         result.write(read_stream);
		}
}

