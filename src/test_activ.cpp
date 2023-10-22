#include "../lib/activation.h"
#include<iostream>
using namespace std;
int main()
{
    cout<<Activation::Sigmoid::function(10)<<"\n";
    cout<<Activation::Sigmoid::derivative(0.5)<<"\n";
    cout<<Activation::Sigmoid::derivative(1.25)<<"\n";
    return 0;
}
