#include "../lib/Regression.h"
#include "../lib/activation.h"
using namespace std;
int main()
{
    ifstream fin;
    ofstream fout;
    fin.open("./data/data_logreg.csv");
    if(!fin)
        cerr<<"Error: File data_linreg.csv opening failed!\n";
    fout.open("./data/LogReg_out.txt");
    if(!fout)
        cerr<<"Error: File LogReg_out.txt opening failed!\n";
    Regression model(1,Activation::Sigmoid::function,Activation::Sigmoid::derivative);
    Dataframe df(fin);
    // model.fit(true,10000,0.05,df,&fout);
    model.fit(false,1000,0.001,df,&fout);
    return 1;
}