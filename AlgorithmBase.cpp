
#include "AlgorithmBase.h"

AlgorithmBase::AlgorithmBase(string graphFile, string reqFile){
    inputGraph(graphFile);
    inputReq(reqFile);
    m_timeslot = 0;
}

// AlgorithmBase::~AlgorithmBase(){
//     for(int i=0;i<(int)m_nodes.size();i++){
//         delete m_nodes[i];
//         m_nodes[i] = nullptr;
//     }
//     m_nodes.clear();
//     for(int i=0;i<(int)graph.size();i++){
//         for(auto &e:graph[i]){
//             if(e.second != nullptr){
//                 delete e.second;
//                 e.second = nullptr;
//             }
//         }
//         graph[i].clear();
//     }
//     m_graph_in.close();
// }

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
        req_in>>m_requests[i].src>>m_requests[i].dst;
        req_in>>m_requests[i].data_size>>m_requests[i].value;
        req_in>>m_requests[i].start>>m_requests[i].deadlines;
        Node *p = m_nodes[m_requests[i].src];
        User *src = dynamic_cast<User *>(p);
        src->add_src(i);

        Node *p2 = m_nodes[m_requests[i].dst];
        User *dst = dynamic_cast<User *>(p2);
        dst->add_dst(i);
    }
    req_in.close();
}

void AlgorithmBase::updateChannel(){
    // release old channel first

    for(int i=0;i<(int)graph.size();i++){
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
        Channel *c = new Channel(m_nodes[u], m_nodes[v], cap);
        graph[u][v] = c;
        c = new Channel(m_nodes[v], m_nodes[u], cap);
        graph[v][u] = c;
    }
}


void AlgorithmBase::addReq(){
    for(int i=0;i<(int)m_requests.size();i++){
        if(m_requests[i].start == m_timeslot){
            Node *p = m_nodes[m_requests[i].src];
            p->dataIn(i, m_requests[i].data_size);
        }
    }
}


void AlgorithmBase::start(){
    for(m_timeslot=0;m_timeslot<m_total_timeslot;m_timeslot++){
        cout<<"m_timeslot: "<<m_timeslot<<endl;
        updateChannel();
        addReq();
        assignChannels();
        nextTimeSlot();
    }
}


void AlgorithmBase::assignChannel(int reqno, int from, int to, long long data_size){
    graph[from][to]->assign(reqno, data_size);
}

void AlgorithmBase::nextTimeSlot(){
    
    for(int i=0;i<(int)graph.size();i++){
        for(auto e:graph[i]){
            if(e.second != nullptr){
                e.second->next_timeslot();
            }
        }
    }
    for(int i=0;i<(int)m_requests.size();i++){
        const Request &r = m_requests[i];
        if(m_timeslot != r.deadlines){
            continue;
        }
        cout<<"request deadline: "<<i<<endl;
        Node *dst = m_nodes[m_requests[i].dst];
        long long arri_data = dst->req_data(i);
        if(arri_data == r.data_size){
            m_res["finishedReq"] += 1;
            m_res["profit"] += r.value;
        }
    }
}


long long AlgorithmBase::getRes(string s){
    return m_res[s];
}