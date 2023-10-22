#include "../lib/dataframe.h"
#include<iostream>

#ifndef _FSTREAM_H
#define _FSTREAM_H
#include<fstream>
#endif

using namespace std;
int main()
{
    ifstream fin("./data/Data.csv",ios::in);
    if(!fin)
    {
        cerr<<"Error: File does not exist\n";
        exit(1);
    }
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
