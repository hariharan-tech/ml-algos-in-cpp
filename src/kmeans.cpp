#include<iostream>
#include<cstdlib>
#include "./../lib/node.h"

std::vector<unsigned int> random_ind(unsigned int min,unsigned int max,int count){
    srand((unsigned) time(NULL)); // seed for random no
    std::vector<unsigned int> ran_nos;
    unsigned int temp;
    while(ran_nos.size()!=count){
        temp = (min + (rand()%(max-min)));
        for(unsigned int i=0;i<ran_nos.size();i++){
            if(ran_nos[i]==temp) continue;
        }
        ran_nos.emplace_back(temp);
    }
    return ran_nos;
}

int main(){

    // Variables
    unsigned int NO_OF_FEATURES = 2, K_VAL = 2;
    
    // Data-preparation
    std::vector<node> points = data_to_nodes(R"(./data/dataset.txt)");

    // Finding K random index values
    std::vector<unsigned int> rand_ind = random_ind(0,10,K_VAL);
    // for(unsigned int i=0;i<ran_ind.size();i++) std::cout<<ran_ind[i]<<", ";

    // Getting K random indexed nodes!
    std::vector<node> k_center;
    for(unsigned int i=0;i<rand_ind.size();i++){
        k_center.emplace_back(points[rand_ind[i]]);
    }


    // K Means clustering
    unsigned int iterations = 5;
    for(unsigned int iter=0;iter<iterations;iter++){
        // all points iteration
        for(unsigned int i=0;i<points.size();i++){
            // calculate distace!
            for(unsigned int j=0;j<K_VAL;j++){
                points[i].distances[j] = dist::euclidean(points[i],k_center[j]);
            }
            // Select the minimum distance and assign that index to the point
            double min_val = 99999.0; unsigned int index = -1;
            for(unsigned int j=0;j<K_VAL;j++){
                if(min_val>points[i].distances[j]){
                    index = j; min_val = points[i].distances[j];
                }
            }
            // Update the assignment..
            points[i].assignment = index;
        }
        for(unsigned int j=0;j<points.size();j++) std::cout<<points[j].assignment<<", ";
        std::cout<<std::endl;
    }
    return 0;
}