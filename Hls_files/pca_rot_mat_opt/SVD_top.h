#ifndef _SVD_TOP_H_
#define _SVD_TOP_H_

#define PRECISION 0.1f
#define DIM 4
#define ENERGY_FACTOR 0.9f
#define L_MAX 3
#include "hls_stream.h"
#include "ap_int.h"
#include "ap_axi_sdata.h"

// struct stream_inp{
//	float data;
//	ap_uint<1> last;
//} ;

typedef hls::axis<float, 0, 0, 0> stream_inp;
typedef hls::stream<stream_inp> mystream;

void pca(mystream &a_in, mystream &sorted_eigvec,int &index_count, float &comp_rate);



//void sort_select(const float eigenvec[DIM*DIM],const float eigen[DIM], float sorted_eigenval[DIM],float sorted_eigenvec[DIM*DIM],int& in, float& comp);
#endif
