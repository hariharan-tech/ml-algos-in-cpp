#include "../lib/Regression.h"
#include "../lib/activation.h"
using namespace std;
int main()
{
    ifstream fin;
    ofstream fout;
    fin.open("./data/data_logreg2d.csv");
    if(!fin)
        cerr<<"Error: File data_logreg.csv opening failed!\n";
    fout.open("./data/LogReg2D_out.txt");
    if(!fout)
        cerr<<"Error: File LogReg2D_out.txt opening failed!\n";
    Regression model(2,Activation::Sigmoid::function,Activation::Sigmoid::derivative);
    Dataframe df(fin);
    // model.fit(true,10000,0.05,df,&fout);
    model.fit(false,1000,0.001,df,&fout);
    return 1;
}