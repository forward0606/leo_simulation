#include "AlgoLP.h"
using namespace std;


int main(){
    vector<string> Y_names = {"finishedReq", "profit"};
    
    string graphFile = "testcase/1.graph";
    string reqFile = "testcase/1.req";
    string lpRes = "testcase/1.lpRes";

    AlgorithmBase *algo =  new AlgoLP(graphFile, reqFile, lpRes);

    algo->start();

    for(const string &s:Y_names){
        cout<<s<<": "<<algo->getRes(s)<<endl;
    }

    // delete algo;

    return 0;
}