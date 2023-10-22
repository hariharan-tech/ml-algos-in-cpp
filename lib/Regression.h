#ifndef _IOSTREAM_H
#include<iostream>
#define _IOSTREAM_H
#endif

#ifndef _STATS_H
#include "statistics.h"
#define _STATS_H
#endif

#ifndef _DATAFRAME_H
#include "dataframe.h"
#define _DATAFRAME_H
#endif

typedef std::vector<std::vector<double>> vvd;

double Identity_der(double);
double Identity(double);

class Regression{
    std::vector<double> weights;
    double bias;
    // double (*activation)(double);
    double (*activation_der)(double)=Identity_der;           // Derivative of the activation function
    double (*activation_func)(double)=Identity;
    bool is_batch;
    void export_weights(std::ofstream*);
    void Back_propagate_batch(unsigned int,std::ofstream*);     // History file
    void Back_propagate_online(unsigned int,std::ofstream*);  
    public:
        int dim;
        double alpha;       // Learning rate
        vvd data_table;
        Regression(unsigned int);   // Dimension
        Regression(std::vector<double>);   // Initial weights
        Regression(unsigned int,double (*)(double),double (*)(double));
        Regression(std::vector<double>,double (*)(double),double (*)(double));
        void fit(unsigned int,double,Dataframe&);       // Double variable is the learning rate
        void fit(bool,unsigned int,double,Dataframe&);  // Batch/Online learning, Number of epochs
        void fit(bool,unsigned int,double,Dataframe&,std::ofstream*);   // For printing 
        // void fit(bool,unsigned int); // Extra is activation function
        double test(std::vector<double>::iterator,std::vector<double>::iterator);
        double test(std::vector<double>::iterator,std::vector<double>::iterator,double);
};
