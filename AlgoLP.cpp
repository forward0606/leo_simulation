#include "AlgoLP.h"


AlgoLP::AlgoLP(string graphFile, string reqFile, string lpResFile)
    :AlgorithmBase(graphFile, reqFile){
        m_LP.open(lpResFile);
        if(m_LP.fail()){
            cout<<"open lp result file error"<<endl;
            exit(1);
        }
}
void AlgoLP::assignChannels(){
    int links;
    m_LP>>links;
    int reqno, from, to;
    long long flow_size;
    for(int i=0;i<links;i++){
        m_LP>>reqno>>from>>to>>flow_size;
        assignChannel(reqno, from, to , flow_size);
    }
}