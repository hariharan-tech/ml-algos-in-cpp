#include "hls_stream.h"
#include "ap_axi_sdata.h"

#define DATA_SIZE 256
#define BANDS 23
#define L_MAX 7

typedef hls::axis<float,0,0,0> s_packet;
typedef hls::stream<s_packet> stream_port;

void projection(stream_port &data,stream_port &eig_vec, stream_port &result);


