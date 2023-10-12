// #include<iostream>
#include "dataframe.h"

Dataframe::Dataframe(std::ifstream &fin)
{
    std::string word;
    while(fin>>word)
    {
        // fin>>word;
        // std::getline(fin,word);
        std::stringstream s(word);
        std::vector<double> row;
        std::string w;
        while(std::getline(s,w,','))
        {
            // std::getline(s,w,',');
            // std::cout<<w<<"\n";
            // std::cout<<w.size()<<"\n";
            row.push_back((double)(std::stod(w)));
            // std::cout<<std::stod(w)<<"\n";
        }
        db_vec.push_back(row);
    }        
}

std::vector<std::vector<double>> Dataframe::extract_vect()
{
    return db_vec;
}

std::vector<std::vector<double>> Dataframe::iloc(p_ui r)
{
    std::vector<std::vector<double>> vec;
    std::copy(db_vec.begin()+r.first,db_vec.begin()+r.second,std::back_inserter(vec));  // std::copy() for deep copy
    return vec;
}

std::vector<std::vector<double>> Dataframe::iloc(p_ui r,p_ui c)
{
    std::vector<std::vector<double>> res;
    // std::vector<std::vector<double>>::iterator start_r,end_r;
    // std::vector<double>::iterator start_c,end_c;
    // start_r=db_vec.begin()+(r.first);
    // end_r=db_vec.begin()+(r.second());
    unsigned int i;
    for(i=r.first;i<r.second;i++)
    {
        std::vector<double> v_row;
        std::copy(db_vec[i].begin()+c.first,db_vec[i].begin()+c.second,std::back_inserter(v_row));
        res.push_back(v_row);
    }
    return res;
}

std::vector<double> Dataframe::iloc(unsigned int r)
{
    return db_vec[r];
}

std::vector<double> Dataframe::iloc(unsigned int r,p_ui c)
{
    std::vector<double> vec;
    std::copy(db_vec[r].begin()+c.first,db_vec[r].end()+c.second,std::back_inserter(vec));
    return vec;
}
