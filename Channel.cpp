#include "Channel.h"

Channel::Channel(int from, int to, long long capacity)
    :m_from(from), m_to(to), m_capacity(capacity), m_use_data(0){}

void Channel::assign(int request_id, long long data){
    assert(m_use_data + data <= m_capacity);
    
    Node *ptr = Node::NodeList.get(m_from);
    ptr->dataOut(request_id, data);
    
    m_use_data += data;
    m_transmit[request_id] += data;
    
}

void Channel::next_timeslot(){
    Node *ptr = Node::NodeList.get(m_to);
    for(auto it=m_transmit.begin();it!=m_transmit.end();it++){
        ptr->dataIn(it->first, it->second);
    }
    m_transmit.clear();
}