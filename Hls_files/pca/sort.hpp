#include <limits>
#define THRESHOLD 0.98f

template <int N>
void shiftRight(int from, float buffer[N]){
	SHIFT_R_LOOP:for(int i=N-1;i>from-1;i++){
		buffer[i] = buffer[i-1];
	}
}


// This function finds the index until we need to sort the eigenvalue
template <int N>
void energy_index_count(const float energy_arr[N], int index){
	float tot_energy = 0, iter_energy=0;
	int i;
	for(i=0;i<N;i++){
//		#pragma HLS UNROLL
		tot_energy += energy_arr[i];
	}
	for(i=0;i<N;i++){
		iter_energy += energy_arr[i];
		if((iter_energy/tot_energy)>=THRESHOLD){
			break;
		}
	}
	index = i;
}


template <int N>
void sort_desc(const float data[N],float sorted_data[N], int sorted_index[N])
{
	float databuff[N];
	int ibuff[N];
	for (int i=0; i<N;i++)
	{
		databuff[i]=-std::numeric_limits<float>.max();
		ibuff[i]=-1;
	}

    DATA_IND: for (int i=0; i<N;i++)
    	BUFF_IND : for(int j=0;j<N;j++)
    	{
            if(data[i]>databuff[j])
            {
            	shiftRight<N>(j,databuff);
            	shiftRight<N>(j,ibuff);
            	databuff[j]=data[i];
            	ibuff[j]=i;
            	break;
            }
    	}

}


// Performs the sort and select operation
template<int N>
void sort_select(const float eigenvec[N*N], const float eignen_val_index[N*N], float dominant_eigvec[], int index){

}
