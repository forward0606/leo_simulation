#ifndef __NODE_H
#define __NODE_H

#include "Container.h"

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cassert>
using namespace std;

class Node{ // some constant 
    int m_id;
    string m_type;          // node type: satellite or user node
    
    long long m_total_storage;      // total storage on this node
    long long m_used_storage;       // number of volume store at the node

    // store[i]: number of data which is belong to request i store at this node
    map<int, long long> m_store;  
public:
    static Container<Node*> NodeList;
    static const long long MAX_STORAGE = 1e11;
    inline const static string SATELLITE = "satellite";
    inline const static string USER = "user";
    
    Node(int id, string type, long long total_storage=MAX_STORAGE);
    int getId();
    string get_type();
    
    /**
     * \brief data transimit to this node
     * \param request_id the request which data related to
     * \param data_size the data size transimit to this node
     */
    virtual void dataIn(int request_id, long long data_size);

    /**
     * \brief data transimit from this node
     * \param request_id the request which data related to
     * \param data_size the data size transimit to this node
     */
    virtual void dataOut(int request_id, long long data_size);

    /**
     * \brief the data of request_id store at this node
     * \param request_id request index
     */
    long long req_data(int request_id);
};


class User: public Node{
    // list of request which source/destination is this node
    set<int> m_src_of_req, m_dst_of_req;
public:
    User(int id);
    void dataIn(int request_id, long long data_size)override;
    void dataOut(int request_id, long long data_size)override;
    void add_src(int request_id);
    void add_dst(int request_id);
};





#endif