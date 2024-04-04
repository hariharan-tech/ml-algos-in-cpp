#include "array_sum.h"
#include <iostream>

void add(data_stream &a_in,data_stream &b_in, data_stream &sum)
{
	#pragma HLS INTERFACE ap_ctrl_none port=return
	#pragma HLS INTERFACE axis port=a_in
	#pragma HLS INTERFACE axis port=b_in
	#pragma HLS INTERFACE axis port=sum

   float a_mem[DIM*DIM], b_mem[DIM*DIM],c_mem[DIM*DIM];
   int i=0;
   stream_inp inp;
   do{
     inp=a_in.read();
     a_mem[i]=inp.data;
     i++;
   }while(!inp.last);

   i=0;

   do{
     inp=b_in.read();
     b_mem[i]=inp.data;
     i++;
   }while(!inp.last);

   for(int index=0;index<DIM*DIM;index++)
   {
       #pragma HLS UNROLL
	   c_mem[index]=a_mem[index]+b_mem[index];
   }

   for(int i=0;i<DIM*DIM;i++)
   {
       inp.data= c_mem[i];
       inp.last= (i==DIM*DIM-1)?1:0;
       sum.write(inp);
   }

}
