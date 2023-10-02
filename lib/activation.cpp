#include "activation.h"

double abs(double x)
{
    if(x<0)
        return (-1)*x;
    return x;
}

double Activation::Identity::function(double y) {return y;}
double Activation::Identity::derivative(double y) {return 1;}

double Activation::Binary_step::function(double y) {return y>=0;}
bool Activation::Binary_step::isvalid(double y) {return (y==0 || y==1);}

double Activation::Sigmoid::function(double y)
{
    return 1/(1+exp((-1)*y));
}
double Activation::Sigmoid::derivative(double y,bool m)
{
    if(m)
    {
        if(!isValid(y))
            exit(1);
        return y*(1-y);
    }
    double a=function(y);
    return a*(1-a);
}
bool Activation::Sigmoid::isValid(double y) {return (y>0 && y<1);}

double Activation::Tanh::function(double y) {return tanh(y);}
double Activation::Tanh::derivative(double y,bool m)
{
    if(m)
    {
        if(!isvalid(y)) 
            exit(1);
        return 1-(y*y);
    }
    double a=function(y);
    return 1-(a*a);
}
bool Activation::Tanh::isvalid(double y) {return abs(y)<1;}

double Activation::ArcTan::function(double y) {return atan(y);}
double Activation::ArcTan::derivative(double y)
{
    return 1/(1+(y*y));
}
bool Activation::ArcTan::isvalid(double y) {return ((y>((-1)*M_PI_2)) && (y<M_PI_2));}

double Activation::Softsign::function(double y)
{
    return y/(1+abs(y));
}
double Activation::Softsign::derivative(double y)
{
    return 1/pow((1+abs(y)),2);
}
bool Activation::Softsign::isvalid(double y) {return abs(y)<1;}

double Activation::ISRU::function(double y,double alpha)
{
    return y/(sqrt(1+(alpha*y*y)));
}
double Activation::ISRU::derivative(double y,double alpha)
{
    return pow(1/(sqrt(1+(alpha*y*y))),3);
}
bool Activation::ISRU::isvalid(double y,double alpha)
{
    double a=1/sqrt(alpha);
    return abs(y)<a;
}

double Activation::ISRLU::function(double y,double alpha)
{
    if(y>=0)
        return y;
    return y/sqrt(1+(alpha*y*y));
}
double Activation::ISRLU::derivative(double y,double alpha)
{
    if(y>=0)
        return 1;
    return y/sqrt(1+(alpha*y*y));
}
bool Activation::ISRLU::isvalid(double y,double alpha)
{
    double a=-1/sqrt(alpha);
    return y>a;
}

double Activation::SQNL::function(double y)
{
    if(y>2)
        return 1;
    if(y>=0)
        return y-(y*y/4);
    if(y>=-2)
        return y+(y*y/4);
    return -1;
}
double Activation::SQNL::derivative(double y)
{
    if(y>2)
        return 0;
    if(y>=0)
        return 1-(y/2);
    if(y>=-1)
        return 1+(y/2);
    return 0;
}
bool Activation::SQNL::isvalid(double y) {return abs(y)<1;}

double Activation::ReLU::function(double y)
{
    if(y<0)
        return 0;
    return y;
}
double Activation::ReLU::derivative(double y,bool m)
{
    if(m)
    {
        if(!isvalid(y))
            exit(1);
        if(y)
            return 1;
        return 0;
    }
    if(y<0)
        return 0;
    return 1;
}
bool Activation::ReLU::isvalid(double y) {return y>=0;}

double Activation::PReLU::function(double y,double alpha)
{
    if(y<0)
        return alpha*y;
    return y;
}
double Activation::PReLU::derivative(double y,double alpha,double m)
{
    if(y<0)
        return alpha;
    return 1;
}

double Activation::LeakyReLU::function(double y,double alpha) {return Activation::PReLU::function(y,0.01);}
double Activation::LeakyReLU::derivative(double y,double alpha,bool m) {return Activation::PReLU::derivative(y,0.01,true);}

double Activation::Softplus::function(double y)
{
    return log(1+exp(y));
}
double Activation::Softplus::derivative(double y)
{
    return 1/(1+exp((-1)*y));
}
bool Activation::Softplus::isvalid(double y) {return y>0;}

double Activation::Bent_Identity::function(double y)
{
    return ((sqrt(pow(y,2)+1)-1)/2)+y;
}
double Activation::Bent_Identity::derivative(double y)
{
    return (y/(2*sqrt(pow(y,2)+1)))+1;
}

double Activation::Sinusoid::function(double y) {return sin(y);}
double Activation::Sinusoid::derivative(double y) {return cos(y);}
bool Activation::Sinusoid::isvalid(double y) {return abs(y)<=1;}

double Activation::Sinc::function(double y)
{
    if(y==0)
        return 1;
    return sin(y)/y;
}
double Activation::Sinc::derivative(double y)
{
    if(y==0)
        return 0;
    return (cos(y)/y)-(sin(y)/pow(y,2));
}
bool Activation::Sinc::isvalid(double y) {return y>=-0.21723363;}

double Activation::Gaussian::function(double y)
{
    return exp((-1)*pow(y,2));
}
double Activation::Gaussian::derivative(double y)
{
    return (-2)*y*exp((-1)*pow(y,2));
}