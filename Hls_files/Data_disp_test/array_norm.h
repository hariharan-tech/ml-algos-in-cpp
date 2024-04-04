#include "hls_stream.h"
#include "ap_axi_sdata.h"
#define DIM 4


typedef hls::axis<float,0,0,0> stream_data;
typedef hls::stream<stream_data> my_stream;
void norm(my_stream &a,my_stream &b);
