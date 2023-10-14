#include "activation.h"

double abs(double x)
{
    if(x<0)
        return (-1)*x;
    return x;
}

namespace Activation{
    namespace Identity{
        double function(double y) {return y;}
        double derivative(double y, bool m) {return 1.0;} 
        double derivative(double y) {return derivative(y,true);}
    }    

    namespace Binary_step{    
        double function(double y) {return y>=0;}
        bool isvalid(double y) {return (y==0 || y==1);}
    }

    namespace Sigmoid{
        double function(double y)
        {
            return 1/(1+exp((-1)*y));
        }
        bool isValid(double y) {return (y>0 && y<1);}
        double derivative(double y,bool m)
        {
            if(m)
            {
                if(!isValid(y))
                { 
                    std::cerr<<"Error: Operand out of function range\n";
                    exit(1);
                }
                return y*(1-y);
            }
            double a=function(y);
            return a*(1-a);
        }
        double derivative(double y) {return derivative(y,true);}
    }

    namespace Tanh{     
        double function(double y) {return tanh(y);}
        bool isvalid(double y) {return abs(y)<1;}
        double derivative(double y,bool m)
        {
            if(m)
            {
                if(!isvalid(y))
                { 
                    std::cerr<<"Error: Operand out of function range\n";
                    exit(1);
                }
                return 1-(y*y);
            }
            double a=function(y);
            return 1-(a*a);
        }
    }

    namespace ArcTan{
        double function(double y) {return atan(y);}
        double derivative(double y)
        {
            return 1/(1+(y*y));
        }
        bool isvalid(double y) {return ((y>((-1)*M_PI_2)) && (y<M_PI_2));}
    }

    namespace Softsign{ 
        double function(double y)
        {
            return y/(1+abs(y));
        }
        double derivative(double y)
        {
            return 1/pow((1+abs(y)),2);
        }
        bool isvalid(double y) {return abs(y)<1;}
    }
    
    namespace ISRU{        
        double function(double y,double alpha)
        {
            return y/(sqrt(1+(alpha*y*y)));
        }
        double derivative(double y,double alpha)
        {
            return pow(1/(sqrt(1+(alpha*y*y))),3);
        }
        bool isvalid(double y,double alpha)
        {
            double a=1/sqrt(alpha);
            return abs(y)<a;
        }
    }

    namespace ISRLU{
        double function(double y,double alpha)
        {
            if(y>=0)
                return y;
            return y/sqrt(1+(alpha*y*y));
        }
        double derivative(double y,double alpha)
        {
            if(y>=0)
                return 1;
            return y/sqrt(1+(alpha*y*y));
        }
        bool isvalid(double y,double alpha)
        {
            double a=-1/sqrt(alpha);
            return y>a;
        }
    }

    namespace SQNL{    
        double function(double y)
        {
            if(y>2)
                return 1;
            if(y>=0)
                return y-(y*y/4);
            if(y>=-2)
                return y+(y*y/4);
            return -1;
        }
        double derivative(double y)
        {
            if(y>2)
                return 0;
            if(y>=0)
                return 1-(y/2);
            if(y>=-1)
                return 1+(y/2);
            return 0;
        }
        bool isvalid(double y) {return abs(y)<1;}
    }

    namespace ReLU{
        double function(double y)
        {
            if(y<0)
                return 0;
            return y;
        }
        double derivative(double y,bool m)
        {
            if(m)
            {
                if(!isvalid(y))
                { 
                    std::cerr<<"Error: Operand out of function range\n";
                    exit(1);
                }
                if(y)
                    return 1;
                return 0;
            }
            if(y<0)
                return 0;
            return 1;
        }
        bool isvalid(double y) {return y>=0;}
    }

    namespace PReLU{
        double function(double y,double alpha)
        {
            if(y<0)
                return alpha*y;
            return y;
        }   
        double derivative(double y,double alpha,double m)
        {
            if(y<0)
                return alpha;
            return 1;
        }
    }

    namespace LeakyReLU{
        double function(double y) {return PReLU::function(y,0.01);}
        double derivative(double y,bool m) {return PReLU::derivative(y,0.01,true);}
    }

    namespace Softplus{
        double function(double y)
        {
            return log(1+exp(y));
        }
        double derivative(double y)
        {
            return 1/(1+exp((-1)*y));
        }
        bool isvalid(double y) {return y>0;}
    }

    namespace Bent_Identity{
        double function(double y)
        {
            return ((sqrt(pow(y,2)+1)-1)/2)+y;
        }
        double derivative(double y)
        {
            return (y/(2*sqrt(pow(y,2)+1)))+1;
        }
    }

    namespace Sinusoid{        
        double function(double y) {return sin(y);}
        double derivative(double y) {return cos(y);}
        bool isvalid(double y) {return abs(y)<=1;}
    }

    namespace Sinc{    
        double function(double y)
        {
            if(y==0)
                return 1;
            return sin(y)/y;
        }
        double derivative(double y)
        {
            if(y==0)
                return 0;
            return (cos(y)/y)-(sin(y)/pow(y,2));
        }
        bool isvalid(double y) {return y>=-0.21723363;}
    }

    namespace Gaussian{        
        double function(double y)
        {
            return exp((-1)*pow(y,2));
        }
        double derivative(double y)
        {
            return (-2)*y*exp((-1)*pow(y,2));
        }
        bool isvalid(double y) {return y<=1;}
    }
}
