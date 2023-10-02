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

namespace Activation{
    namespace Identity{                 // The Identity activation function
        double function(double y);
        double derivative(double y);
    }
    namespace Binary_step{              // Binary step function
        double function(double y);      //Not differentiable at y=0
        // double derivative(double y);
        bool isvalid(double y);
    }
    namespace Sigmoid{                  // Binary sigmoidal activation function
        double function(double y);
        double derivative(double y,bool m);
        bool isValid(double y);
    }
    namespace Tanh{                     // Tanh activation function
        double function(double y);
        double derivative(double y,bool m);
        bool isvalid(double y);
    }
    namespace ArcTan{                   // Inverse Tan activation function
        double function(double y);
        double derivative(double y);
        bool isvalid(double y);
    }
    namespace Softsign{                 // Elliotsig/Softsign activation function
        double function(double y);
        double derivative(double y);
        bool isvalid(double y);
    }
    namespace ISRU{                     // Inverse Square Root activation function
        double function(double y,double alpha);
        double derivative(double y,double alpha);
        bool isvalid(double y,double alpha);
    }    
    namespace ISRLU{                    // Inverse Square Root Linear acivation function
        double function(double y,double alpha);
        double derivative(double y,double alpha);
        bool isvalid(double y,double alpha);
    }
    namespace SQNL{                     // Square Nonlinearity activation function
        double function(double y);
        double derivative(double y);
        bool isvalid(double y);
    }
    namespace ReLU{                     // Rectified Linear Unit activation function 
        double function(double y);
        double derivative(double y,bool m);
        bool isvalid(double y);
    }
    namespace LeakyReLU{                // Leaky Rectified Linear Unit activation function  
        double function(double y);
        double derivative(double y,bool m);
    }
    namespace PReLU{                    // Parametric Recified Linear Unit activation function
        double function(double y,double alpha);
        double derivative(double y,double alpha,double m);
    }
    // Randomized ReLU to be confirmed before adding
    namespace Softplus{                 // Softplus activation function
        double function(double y);
        double derivative(double y);
        bool isvalid(double y);
    } 
    namespace Bent_Identity{            // Bent Identity actiavtion function
        double function(double y);
        double derivative(double y);
    }
    // namespace Soft_Exponential{         // Soft Exponential activation function
    //     double function(double y);
    //     double derivative(double y);
    // }
    // namespace Soft_Clipping{            // Soft Clipping activation function
    //     double function(double y);
    //     double derivative(double y);
    // }
    namespace Sinusoid{                 // Sinusoid activation function
        double function(double y);
        double derivative(double y);
        bool isvalid(double y);
    }
    namespace Sinc{                     // Sinc activation function
        double function(double y);
        double derivative(double y);
        bool isvalid(double y);
    }
    namespace Gaussian{                 // Gaussian activation function
        double function(double y);
        double derivative(double y);
        bool isvalid(double y);
    }
}