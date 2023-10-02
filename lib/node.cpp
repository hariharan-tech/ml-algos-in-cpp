#include "node.h"
#include<iostream>

double dist::euclidean(node n1, node n2){
    double dist = 0;
    for(unsigned int i=0;i<n1.f_dim;i++){
        dist += powf64(n1.features[i]-n2.features[i],2);
    }
    return powf64(dist,0.5);
}

std::vector<node> data_to_nodes(std::string file_name){
    std::ifstream newfile(file_name.c_str());
    std::vector<node> points;
    if (!newfile.is_open())
    {
        std::cout << "Error: Failed to open file." << std::endl;
        exit(1);
        // return 1;
    }
    std::string line;
    std::vector<double> temp;
    while(getline(newfile,line)){
        std::string val = "";
        for(int i=0;i<=line.length();i++){
            if(line[i]==','||line[i]=='\0'){
                temp.emplace_back(std::stod(val));
                // std::cout<<val<<std::endl;
                val="";
            }
            else{
                val+=line[i];
            }
        }
        // node temp_node = node(temp.size(),temp);
        points.emplace_back(node(temp.size(),temp));
        temp.clear();
    }
    newfile.close();
    return points;
}