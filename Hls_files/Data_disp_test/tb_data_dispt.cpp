#include <cstdlib>
#include <iostream>
#include "data_dispt.h"
#include "array_norm.h"
#include "array_sum.h"

float genRandFloat(){
	return (float)rand()/(float)rand();
}

int main(void){
	stream_inp ip_s_packet, op_s1_packet, op_s2_packet;
	data_stream inp_stream, op_stream1, op_stream2, temp_stream,result_stream;


	//software verification
	float a_sw[DIM*DIM],b_sw[DIM*DIM],c_sw[DIM*DIM];
	float input_data[TOTAL_DATA_COUNT];
	float total=0;
	int sw_index;

	for(int i=0;i<TOTAL_DATA_COUNT;i++){
		input_data[i] = genRandFloat();
	}
	for(int i=0;i<TOTAL_DATA_COUNT;i++)
		std::cout<<input_data[i]<<" ";

	for(sw_index=0;sw_index<DIM*DIM;sw_index++){
		a_sw[sw_index]=input_data[sw_index];
		total+=a_sw[sw_index];
	}


	for(int i=0;i<DIM*DIM;i++){
		a_sw[i]/=total;
	}
	for(int i=0;i<DIM*DIM;i++){
		b_sw[i]=input_data[i+sw_index];
	}

	for(int i=0;i<DIM*DIM;i++){
		c_sw[i]=a_sw[i]+b_sw[i];
	}


	// Generate packets and write to input_stream
	for(int i=0;i<TOTAL_DATA_COUNT;i++){
		ip_s_packet.data = input_data[i];
		ip_s_packet.last = (i==TOTAL_DATA_COUNT-1)?1:0;
		inp_stream.write(ip_s_packet);
	}
	// Call the hardware functions
	int err=0, index=0;
	data_dispatcher(inp_stream,op_stream1,op_stream2);

    float op_s1_arr[DIM*DIM], op_s2_arr[DIM*DIM];

    std::cout<<std::endl;

    do{
    	op_s1_packet = op_stream1.read();
    	op_s1_arr[index++] = op_s1_packet.data;
    	std::cout<<op_s1_packet.data<<" ";
    }while(!op_s1_packet.last);

    index = 0;
    std::cout<<std::endl;

    do{
		op_s2_packet = op_stream2.read();
		op_s2_arr[index++] = op_s2_packet.data;
		std::cout<<op_s2_packet.data<<" ";
	}while(!op_s2_packet.last);

    for(int i=0;i<DIM*DIM;i++){
    	if(input_data[i]!=op_s1_arr[i]) err++;
    }
    for(int i=DIM*DIM;i<TOTAL_DATA_COUNT;i++){
		if(input_data[i]!=op_s2_arr[i-DIM*DIM]) err++;
	}


//    norm(op_stream1,temp_stream);
//    add(op_stream2,temp_stream,result_stream );
//    std::cout<<std::endl;
//	do{
//		op_s2_packet = result_stream.read();
//		result_stream_arr[index]=op_s2_packet.data;
//		index++;
//	}while(!op_s2_packet.last);
//
//		std::cout<<std::endl;
//	for(int i=0;i<DIM*DIM;i++){
//		std::cout<<result_stream_arr[i]<<" ";
//		if(result_stream_arr[i]!=c_sw[i])
//			err++;
//	}
//
	if(err==0) std::cout<<"\nNo errors found!\n\n";
	else std::cout<<"\nMatch not found!\n\n";

}
