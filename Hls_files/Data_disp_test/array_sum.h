#include "hls_stream.h"
#include "ap_axi_sdata.h"

#define DIM 4

typedef hls::axis<float,0,0,0> stream_inp;
typedef hls::stream<stream_inp> data_stream;

void add(data_stream &a_in,data_stream &b_in, data_stream &sum);

