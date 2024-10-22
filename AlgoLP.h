#ifndef __ALGO_LP_H
#define __ALGO_LP_H

#include "AlgorithmBase.h"

#include <fstream>



class AlgoLP: public AlgorithmBase{
    fstream m_LP;
public:
    AlgoLP(string graphFile, string reqFile, string lpResFile);
    void assignChannels() override;
};

#endif