#include "Node.h"



Node::Node(int id, string type, long long storage)
    :m_id(id), m_type(type), m_total_storage(storage), m_used_storage(0){
}


int Node::getId(){
    return m_id;
}
string Node::get_type(){
    return m_type;
}

void Node::dataIn(int request_id, long long data_size){
    // check whether storage limit exceed
    assert(m_used_storage + data_size <= m_total_storage);
    m_used_storage += data_size;
    m_store[request_id] += data_size;
}

void Node::dataOut(int request_id, long long data_size){
    assert(m_store[request_id] >= data_size);
    assert(m_used_storage >= data_size);
    m_used_storage -= data_size;
    m_store[request_id] -= data_size;
}

long long Node::req_data(int request_id){
    return m_store[request_id];    
}



User::User(int id):Node(id, Node::USER){}

void User::dataIn(int request_id, long long data_size){
    // cout<<"dataIn("<<request_id<<", "<<data_size<<")"<<endl;
    // assert(m_dst_of_req.find(request_id) != m_dst_of_req.end());
    Node::dataIn(request_id, data_size);
}

void User::dataOut(int request_id, long long data_size){
    // cout<<"dataOut("<<request_id<<", "<<data_size<<")"<<endl;
    assert(m_src_of_req.find(request_id) != m_src_of_req.end());
    Node::dataOut(request_id, data_size);
}

void User::add_src(int request_id){
    m_src_of_req.insert(request_id);
}

void User::add_dst(int request_id){
    m_dst_of_req.insert(request_id);
}