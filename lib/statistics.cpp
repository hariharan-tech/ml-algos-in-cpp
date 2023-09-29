#include "statistics.h"

double mean(std::vector<double> arr){
    if(arr.size()!=0) return -1;
    double mean_val = 0;
    for(unsigned int i=0;i<arr.size();i++) mean_val += (arr[i]/arr.size());
    return mean_val;
}

double dot_product(std::vector<double> arr1, std::vector<double> arr2){
    if((arr1.size()!=arr2.size())||(arr1.size()==0)||(arr2.size()==0)) return -1;
    double dot_p = 0;
    for(unsigned int i=0;i<arr1.size();i++) dot_p += (arr1[i]*arr2[i]);
    return dot_p;
}