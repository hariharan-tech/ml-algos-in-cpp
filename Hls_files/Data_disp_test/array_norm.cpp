#include"array_norm.h"
void norm(my_stream &a,my_stream &b){
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis port=a
#pragma HLS INTERFACE axis port=b
    stream_data temp;
    float a_in[DIM*DIM];
    int index=0;
    do{
    	temp=a.read();
        a_in[index]=temp.data;
        index++;
    } while(!temp.last);


    float sum=0;
   SUM_LOOP: for (int i=0;i<DIM*DIM;i++){
#pragma HLS UNROLL
	   sum+=a_in[i];
   }

   AVG_LOOP: for (int i=0;i<DIM*DIM;i++){
     a_in[i]=a_in[i]/sum;
   }

   WRITE_LOOP: for(int i=0;i<DIM*DIM;i++){
	   temp.data=a_in[i];
	   temp.last=(i==(DIM*DIM-1))?1:0;
	   b.write(temp);
   }
}
