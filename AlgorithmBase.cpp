
#include "AlgorithmBase.h"

AlgorithmBase::AlgorithmBase(string graphFile, string reqFile){
    inputGraph(graphFile);
    inputReq(reqFile);
    m_timeslot = 0;
}

void AlgorithmBase::inputGraph(string file){
    m_graph_in.open(file);
    if(m_graph_in.fail()){
        cout << "input file opening failed";
        exit(1); // 程式錯誤終止
    }
    int n_node, n_satellite;
    m_graph_in>>n_node>>n_satellite>>m_total_timeslot;
    graph.resize(n_node);
    long long storage;
    for(int i=0;i<n_satellite;i++){
        m_graph_in>>storage;
        Node *p = new Node(i, Node::SATELLITE, storage);
        m_nodes.emplace_back(p);
    }
    for(int i=n_satellite;i<n_node;i++){
        Node *p = new User(i);
        m_nodes.emplace_back(p);
    }
}

void AlgorithmBase::inputReq(string file){
    fstream req_in(file);
    if(req_in.fail()){
        cout<<"request file input error";
        exit(1);
    }
    int n_req;
    req_in>>n_req;
    m_requests.resize(n_req);
    for(int i=0;i<n_req;i++){
        cin>>m_requests[i].src>>m_requests[i].dst;
        cin>>m_requests[i].data_size>>m_requests[i].value;
        cin>>m_requests[i].start>>m_requests[i].deadlines;
    }
    req_in.close();
}

void AlgorithmBase::updateChannel(){
    // release old channel first

    for(int i=0;i<graph.size();i++){
        for(auto &e:graph[i]){
            if(e.second != nullptr){
                delete e.second;
                e.second = nullptr;
            }
        }
        graph[i].clear();
    }
    
    int links;
    m_graph_in>>links;
    int u, v;
    long long cap;
    for(int i=0;i<links;i++){
        m_graph_in>>u>>v>>cap;
        Channel *c = new Channel(u, v, cap);
        graph[u][v] = c;
        c = new Channel(v, u, cap);
        graph[v][u] = c;
    }
}

void AlgorithmBase::start(){
    for(m_timeslot=0;m_timeslot<m_total_timeslot;m_timeslot++){
        updateChannel();
        assignChannels();
        nextTimeSlot();
    }
}


void AlgorithmBase::assignChannel(int reqno, int from, int to, long long data_size){
    graph[from][to]->assign(reqno, data_size);
}

void AlgorithmBase::nextTimeSlot(){
    
    for(int i=0;i<graph.size();i++){
        for(auto e:graph[i]){
            if(e.second != nullptr){
                e.second->next_timeslot();
            }
        }
    }
}
