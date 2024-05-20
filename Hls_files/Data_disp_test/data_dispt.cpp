#include "data_dispt.h"

void data_dispatcher(data_stream &inp_stream, data_stream &op_stream1, data_stream &op_stream2){
	#pragma HLS INTERFACE mode=ap_ctrl_none port=return
	#pragma HLS INTERFACE mode=axis port=inp_stream
	#pragma HLS INTERFACE mode=axis port=op_stream1
	#pragma HLS INTERFACE mode=axis port=op_stream2

	stream_inp i_inp;
	DATA_STREAM: for(int i=0;i<TOTAL_DATA_COUNT;i++){
		i_inp = inp_stream.read();
		if(i<DIM*DIM){
			i_inp.last = (i==DIM*DIM-1)?1:0;
			op_stream1.write(i_inp);
		}
		else{
			i_inp.last = (i==TOTAL_DATA_COUNT-1)?1:0; // This line isn't necessary though
			op_stream2.write(i_inp);
		}
	}
}
