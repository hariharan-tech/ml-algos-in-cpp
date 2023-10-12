#ifndef _IOSTREAM_H
#include<iostream>
#define _IOSTREAM_H
#endif

#ifndef _STATS_H
#include "statistics.h"
#define _STATS_H
#endif

class Regression{
    std::vector<double> weights;
    double bias;
    double (*activation)(double);
    double (*activation_der)(double,bool);
    bool is_batch;
    void Back_propagate_batch(unsigned int);
    void Back_propagate_online(unsigned int); 
    public:
        int dim;
        double alpha;       // Learning rate
        Regression(unsigned int);
        Regression(unsigned int,std::vector<double>);
        void fit(unsigned int);
        void fit(bool,unsigned int);             // Batch/Online learning, Number of epochs
        void fit(bool,std::string,unsigned int); // Extra is activation function
        double test(std::vector<double>);
};
