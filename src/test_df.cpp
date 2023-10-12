#include "dataframe.h"
#include<iostream>

#ifndef _FSTREAM_H
#define _FSTREAM_H
#include<fstream>
#endif

using namespace std;
int main()
{
    ifstream fin("Data.csv",ios::in);
    vector<vector<double>> v;
    // fin.open("Data.csv",ios::in);
    Dataframe df(fin);
    // v=df.extract_vect();
    v=df.iloc({0,2},{1,5});
    for(auto i:v)
    {
        for(auto j:i)
            cout<<j<<"\t";
        cout<<"\n";
    }   
    return 0;
}