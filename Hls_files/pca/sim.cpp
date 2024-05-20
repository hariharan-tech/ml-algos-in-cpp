#include<iostream>
#include<limits>

 #define DIM 4

template <int N,typename T>
void shiftRight(int from, T buffer[N]){
	SHIFT_R_LOOP:for(int i=N-1;i>from-1;i--){
        std::cout<<buffer[i-1]<<"\t";
		buffer[i] = buffer[i-1];
	}
    std::cout<<std::endl;
}

template <int N>
void sort_desc(const float data[N],float sorted_data[N], int sorted_index[N])
{
	float databuff[N];
	int ibuff[N];
	BUFF_INIT_LOOP:for (int i=0; i<N;i++)
	{
		#pragma HLS UNROLL
		databuff[i]=std::numeric_limits<float>::lowest();
		ibuff[i]=-1;
	}


    DATA_IND: for (int i=0; i<N;i++){
    	BUFF_IND : for(int j=0;j<N;j++)
    	{
            if(data[i]>databuff[j])
            {
            	shiftRight<N,float>(j,databuff);
            	shiftRight<N,int>(j,ibuff);
            	databuff[j]=data[i];
            	ibuff[j]=i;
                for(int k=0;k<DIM;k++) std::cout<<databuff[k]<<"\t";
            	break;
            }
        }
        std::cout<<std::endl<<std::endl;
    }

    SORTED_WRITE_LOOP:for(int i=0;i<N;i++)
    {
    	sorted_data[i] = databuff[i];
    	sorted_index[i] = ibuff[i];
    }
}

int main(){
    float test_arr[DIM] = {4.0,2.0,5.0,1.0}, sorted_data[DIM];
    int sorted_ind[DIM];
    sort_desc<DIM>(test_arr,sorted_data,sorted_ind);
    return 0;

}