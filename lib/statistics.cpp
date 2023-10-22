// Cmd to generate asm file: 
// g++ -S -fverbose-asm .\lib\statistics.cpp -o stats.asm

#include "statistics.h"

// template <typename T> T mean(std::vector<T> arr){
double stats::mean(std::vector<double> arr){
    if(arr.size()==0) exit(-1);
    double mean_val = 0;
    for(unsigned int i=0;i<arr.size();i++) 
        mean_val += (arr[i]);
    return mean_val/arr.size();
}

double stats::dot(std::vector<double> arr1, std::vector<double> arr2){
    if((arr1.size()!=arr2.size())||(arr1.size()==0)||(arr2.size()==0))
    {
        std::cerr<<"The dimensions of the two input vectors "<<arr1.size()<<" and "<<arr2.size()<<" don't match!\n";
        exit(-1);
    }
    double dot_p = 0;
    for(unsigned int i=0;i<arr1.size();i++) 
        dot_p += (arr1[i]*arr2[i]);
    return dot_p;
}
