#ifndef _VECTOR_H
#include<vector>
#define _VECTOR_H
#endif

#ifndef _CSTDLIB
#include<cstdlib>
#define _CSTDLIB
#endif

#ifndef _MATH_H
#include<cmath>
#define __MATH_H
#endif

#ifndef _FSTREAM_H
#include<fstream>
#define _FSTREAM_H
#endif

#ifndef _SSTREAM_H
#include<sstream>
#define _SSTREAM_H
#endif

#ifndef _STRING_H
#include<string>
#define _STRING_H
#endif

#ifndef _ALGORITHM_H
#include<algorithm>
#define _ALGORITHM_H
#endif

typedef std::pair<unsigned int,unsigned int> p_ui;

class Dataframe{
    std::vector<std::vector<double>> db_vec;
    public:
        Dataframe(std::ifstream&);
        std::vector<std::vector<double>> extract_vect();
        std::vector<std::vector<double>> iloc(p_ui);            // Obtain the starting and ending rows
        std::vector<std::vector<double>> iloc(p_ui,p_ui);       // Obtain the starting and ending rows and columns
        std::vector<double> iloc(unsigned int);    // Obtain the row index
        std::vector<double> iloc(unsigned int,p_ui);    // Obtain the orw index, from and to columns
};