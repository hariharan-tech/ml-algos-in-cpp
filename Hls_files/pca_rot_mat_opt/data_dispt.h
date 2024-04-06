#include "hls_stream.h"
#include "ap_axi_sdata.h"

#define DATA_SIZE 256
#define BANDS 23

#define TOTAL_DATA_COUNT (BANDS*BANDS)+(DATA_SIZE*BANDS)

typedef hls::axis<float,0,0,0> stream_inp;
typedef hls::stream<stream_inp> data_stream;

void data_dispatcher(data_stream &inp_stream, data_stream &svd_stream, data_stream &pu_stream);
