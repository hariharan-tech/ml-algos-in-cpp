#ifndef _VECTOR_H
#include <vector>
#define _VECTOR_H
#endif

#ifndef _MATH_H
#include <math.h>
#define _MATH_H
#endif

#ifndef _FSTREAM_H
#include <fstream>
#define _FSTREAM_H
#endif

#ifndef _CSTDLIB
#include <cstdlib>
#define _CSTDLIB
#endif

#ifndef _STRING
#include <string>
#define _STRING
#endif

typedef struct node{
    std::vector<double> features;
    unsigned int f_dim;
    unsigned int assignment;
    std::vector<double> distances;
    node(unsigned fe_dim, std::vector<double> feat){
        features = feat;
        f_dim = fe_dim;
        assignment = feat.size();
        // Resetting distance to 0 from all points
        std::vector<double> zeros(fe_dim,0);
        distances = zeros;
    }
}node;


namespace dist{
    double euclidean(node n1, node n2);
};

std::vector<node> data_to_nodes(std::string file_name);