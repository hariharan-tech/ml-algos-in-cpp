#include "Regression.h"

Regression::Regression(unsigned int n)
{
    dim=n;
}
Regression::Regression(unsigned int n,std::vector<double> v)
{
    dim=n;
    weights=v;
}

double Regression::test(std::vector<double> test_v)
{
    return stats::dot(weights,test_v)+bias;
}

void Regression::fit(unsigned int epochs)
{
    fit(true,epochs);
}
void Regression::fit(bool is_batch,unsigned int epochs)
{
    if(is_batch)
        Back_propagate_batch(epochs);
    else
        Back_propagate_online(epochs);
}

void Regression::Back_propagate_batch(unsigned int epochs)
{
    unsigned int i,j,n=weights.size();
    for(i=0;i<epochs;i++)
    {
        for(j=0;j<n;j++)
        {
            weights+=()
        }
    }
}