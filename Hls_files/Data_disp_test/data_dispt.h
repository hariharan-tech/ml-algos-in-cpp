#include "hls_stream.h"
#include "ap_axi_sdata.h"

#define DIM 4
#define TOTAL_DATA_COUNT (DIM*DIM)+(DIM*DIM)

typedef hls::axis<float,0,0,0> stream_inp;
typedef hls::stream<stream_inp> data_stream;

void data_dispatcher(data_stream &inp_stream, data_stream &op_stream1, data_stream &op_stream2);
