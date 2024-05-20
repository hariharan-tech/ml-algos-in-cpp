#include "data_dispt.h"

void data_dispatcher(data_stream &inp_stream, data_stream &svd_stream, data_stream &pu_stream){
	#pragma HLS INTERFACE mode=ap_ctrl_none port=return
	#pragma HLS INTERFACE mode=axis port=inp_stream
	#pragma HLS INTERFACE mode=axis port=svd_stream
	#pragma HLS INTERFACE mode=axis port=pu_stream

	stream_inp i_inp;
	DATA_STREAM: for(int i=0;i<TOTAL_DATA_COUNT;i++){
		i_inp = inp_stream.read();
		if(i<BANDS*BANDS){
			i_inp.last = (i==BANDS*BANDS-1)?1:0;
			svd_stream.write(i_inp);
		}
		else{
			i_inp.last = (i==TOTAL_DATA_COUNT-1)?1:0; // This line isn't necessary though
			pu_stream.write(i_inp);
		}
	}
}
