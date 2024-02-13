#include <limits>
#include "SVD_top.h"

template <int N,typename T>
void shiftRight(int from, T buffer[N]){
	SHIFT_R_LOOP:for(int i=N-1;i>from;i--){
		buffer[i] = buffer[i-1];
	}
}


// This function finds the index until we need to sort the eigenvalue
template <int N>
void energy_index_count(const float energy_arr[N], int& index, float& compression){
	float tot_energy = 0, sorted_eig[N], temp, cummulative_eig[N];
	int i;
//	READ_ARR_LOOP:for(i=0;i<N;i++){
//		sorted_eig[i] = energy_arr[i];
//	}

	TOTAL_ENERGY_LOOP:for(i=0;i<N;i++){
		#pragma HLS UNROLL
		tot_energy += energy_arr[i];
		cummulative_eig[i] = tot_energy;
	}

	ENERGY_THRESHOLD_LOOP:for(i=0;i<N;i++){
		if(cummulative_eig[i]/tot_energy>=ENERGY_FACTOR){
			break;
		}
//		iter_energy += energy_arr[i];
	}
	// returns the number of principle components // Need to cap this to L_MAX if greater!
	index = (i>L_MAX)?(L_MAX):(i);
	compression = cummulative_eig[index-1]/tot_energy; // Returns the compression or representation ratio
}


template <int N>
void sort_desc(const float data[N],float sorted_data[N], int sorted_index[N])
{
	float databuff[N];
	int ibuff[N];
	BUFF_INIT_LOOP:for (int i=0; i<N;i++)
	{
		#pragma HLS UNROLL
		databuff[i]=-std::numeric_limits<float>::max();
		ibuff[i]=-1;
	}


    DATA_IND: for (int i=0; i<N;i++)
    	BUFF_IND : for(int j=0;j<N;j++)
    	{
            if(data[i]>databuff[j])
            {
            	shiftRight<N,float>(j,databuff);
            	shiftRight<N,int>(j,ibuff);
            	databuff[j]=data[i];
            	ibuff[j]=i;
            	break;
            }
        }

    SORTED_WRITE_LOOP:for(int i=0;i<N;i++)
    {
    	sorted_data[i] = databuff[i];
    	sorted_index[i] = ibuff[i];
    }
}

template <int N>
void sort_eigenvector(const float eigenvec[N*N],const int indices[N], int index, float sort_eigenvec[N*N]){
	int temp;
	SELECT_SORTED_EIGENVEC_R:for(int i=0;i<index;i++){
		temp=indices[i];
		SELECT_SORTED_EIGENVEC_C:for(int j=0;j<N;j++){
			#pragma HLS PIPELINE II=1
			sort_eigenvec[i*N+j] = eigenvec[temp*N+j];
		}
	}
}
