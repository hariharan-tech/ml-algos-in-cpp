#ifndef _SVD_TOP_H_
#define _SVD_TOP_H_

#define PRECISION 0.1f
#define DIM 23
#define ENERGY_FACTOR 0.9f
#define L_MAX 7
#include "hls_stream.h"
#include "ap_int.h"
#include "ap_axi_sdata.h"


typedef hls::axis<float, 0, 0, 0> s_packet;
typedef hls::stream<s_packet> stream_port;

void svd_sort_select(stream_port &a_in, stream_port &sorted_eigvec,int &index_count, float &comp_rate);



//void sort_select(const float eigenvec[DIM*DIM],const float eigen[DIM], float sorted_eigenval[DIM],float sorted_eigenvec[DIM*DIM],int& in, float& comp);
#endif
