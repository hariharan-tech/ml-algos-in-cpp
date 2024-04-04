#include"array_norm.h"
#include <iostream>

int main(void)
{
	float a[DIM*DIM] = {2.0,1.0,1.0,1.0};
  	stream_data inp;
    my_stream a_in,b_out;
  	for(int i=0;i<DIM*DIM;i++){
  		inp.data=a[i];
  		inp.last=(i==DIM*DIM-1)?1:0;
  	    a_in.write(inp);
 }

  	norm(a_in,b_out);
    float out_data[DIM*DIM];
    int i=0;
  	do{
  		inp=b_out.read();
  		out_data[i]=inp.data;
  		i++;

  	}while(inp.last!=1);


  	for(int j=0;j<DIM;j++){
  		for(int p=0;p<DIM;p++){
  		  std::cout<<out_data[j*DIM+p]<<" ";
  		}
  		std::cout<<"\n";
  	}
}
