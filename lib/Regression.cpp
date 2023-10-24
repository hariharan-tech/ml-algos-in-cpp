#include "Regression.h"

double Identity_der(double x) {return 1;}
double Identity(double x) {return x;}

Regression::Regression(unsigned int n)
{
    dim=n;
    weights.resize(dim,0);
}
Regression::Regression(std::vector<double> v)
{
    dim=v.size();
    weights=v;
}
Regression::Regression(unsigned int n,double (*activ_func)(double),double (*activ_der)(double))
{
    dim=n;
    weights.resize(dim,0);
    activation_der=activ_der;
    activation_func=activ_func;
}
Regression::Regression(std::vector<double> v,double (*activ_func)(double),double (*activ_der)(double))
{
    dim=v.size();
    weights=v;
    activation_der=activ_der;
    activation_func=activ_func;
}

void Regression::export_weights(std::ofstream* hist)
{
    *hist<<"\n";
    for(int i=0;i<dim;i++)
        *hist<<std::to_string(weights[i])<<" ";
    *hist<<std::to_string(bias)<<" ";
}

double Regression::test(std::vector<double>::iterator v1,std::vector<double>::iterator v2)
{
    std::vector<double> test_v(v1,v2);
    return activation_func(stats::dot(weights,test_v)+bias);
}   
double Regression::test(std::vector<double>::iterator v1,std::vector<double>::iterator v2,double threshold)
{
    return test(v1,v2)>=threshold;
}

void Regression::fit(bool is_batch,unsigned int epochs,double alpha,Dataframe& df,std::ofstream* hist)
{
    this->alpha=alpha;
    data_table=df.extract_vect();
    if(data_table[0].size()!=dim+1)   // Entries of a single row of the dataframe: x(n-1), x(n-2), ... , x1 , y => n-1+1 = dim 
    {
        std::cerr<<"Error: Dimension of the linear regression and dataframe don't match";
        exit(1);
    }
    if(is_batch)
        Back_propagate_batch(epochs,hist);
    else
        Back_propagate_online(epochs,hist);
}
void Regression::fit(bool is_batch,unsigned int epochs,double alpha,Dataframe& df)
{
    fit(is_batch,epochs,alpha,df,NULL);
}
void Regression::fit(unsigned int epochs,double alpha,Dataframe& df)
{
    fit(true,epochs,alpha,df,NULL);
}

void Regression::Back_propagate_batch(unsigned int epochs,std::ofstream* hist)
{
    unsigned int i,j,k,n=data_table.size();
    double w,wb;
    std::vector<double> diff(n,0),y(n,0),inc(n,0);     // Vector of predictions made for each training example; update once every epoch
    // if(!hist)
    //     std::cerr<<"Error: Empty file!\n";
    // else    
    //     std::cerr<<"Success: File exists!\n";
    for(i=0;i<epochs;i++)
    {
        // std::cout<<"Entered here!\n";
        for(j=0;j<n;j++)
        {
            y[j]=test(data_table[j].begin(),data_table[j].begin()+dim);
            diff[j]=data_table[j][dim]-y[j];
        }
        if(hist)
        {
            // std::cout<<"Entered!\n";
            double l=0,loss;
            for(j=0;j<n;j++)
                l+=pow(diff[j],2);
            loss=l/(2*n);
            // std::cout<<"Entered: "<<loss<<"\n";
            *hist<<std::to_string(loss)<<"\n";
        }
        for(j=0;j<n;j++)
            inc[j]=diff[j]*activation_der(y[j]);
        wb=std::accumulate(inc.begin(),inc.end(),0);
        for(k=0;k<dim;k++)
        {
            w=0;
            for(j=0;j<n;j++)
            {
                w+=inc[j]*data_table[j][k];
                // wb+=inc[j];
            }
            weights[k]+=(alpha*w/n);
        }
        bias+=(alpha*wb/n);
    }
    if(hist)
        export_weights(hist);
}

void Regression::Back_propagate_online(unsigned int epochs,std::ofstream* hist)
{
    unsigned int i,j,k,n=data_table.size();
    double w,wb,inc,y;
    std::vector<double> diff(n,0); // ,y(n,0);     // Vector of predictions made for each training example; update once every epoch
    for(i=0;i<epochs;i++)
    {
        if(hist)
        {
            double l=0;
            for(j=0;j<n;j++)
            {
                y=test(data_table[j].begin(),data_table[j].begin()+dim);
                l+=pow(data_table[j][dim]-y,2);
            }
            *hist<<std::to_string(l/(2*n))<<"\n";
        }
        for(j=0;j<n;j++)
        {
            y=test(data_table[j].begin(),data_table[j].begin()+dim);
            inc=(data_table[j][dim]-y)*activation_der(y);
            for(k=0;k<dim;k++)
                weights[k]+=(alpha*inc*data_table[j][k]);
            bias+=(alpha*inc);
        }
    }
    if(hist)
        export_weights(hist);
}
