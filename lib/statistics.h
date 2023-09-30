#ifndef _VECTOR_H
#include <vector>
#define _VECTOR_H
#endif

#ifndef _CSTDLIB
#include <cstdlib>
#define _CSTDLIB
#endif

namespace stats{
    double mean(std::vector<double> arr);

    double dot(std::vector<double> arr1, std::vector<double> arr2);
}