#ifndef __ALGO_BASE_H
#define __ALGO_BASE_H

#include "Node.h"
#include "Channel.h"


#include <vector>
#include <fstream>
using namespace std;

struct Request{
    int src, dst;
    long long data_size;
    long long value;
    int start;
    int deadlines;
    Request(){}
};

class AlgorithmBase{
    fstream m_graph_in;
    int m_total_timeslot, m_timeslot;
    vector<map<int, Channel *>> graph;
    vector<Node *> m_nodes;
    vector<Request> m_requests;
    map<string, long long> m_res;
public:
    AlgorithmBase(string graphFile, string reqFile);
    // ~AlgorithmBase();
    void inputGraph(string file);
    void inputReq(string file);
    void updateChannel();
    void start();
    void addReq();
    virtual void assignChannels()=0;
    void assignChannel(int reqno, int from, int to, long long data_size);
    void nextTimeSlot();
    long long getRes(string s);
};

#endif