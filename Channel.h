#ifndef __CHANNEL_H
#define __CHANNEL_H

#include "Node.h"

#include <map>
using namespace std;

class Channel{
    Node *m_from, *m_to;
    long long m_capacity;           // the number of data this link can transmit within a timeslot
    long long m_use_data;
    map<int, long long> m_transmit;    // transmit[i]: the number of data of request i to transmit with this channel
public:
    
    /**
     * \brief constructor of channel
     * \param from the form node id
     * \param to next hop node id
     * \param capacity link transmit limit
     */
    Channel(Node *from, Node *to, long long capacity);
    void assign(int request_id, long long data); // the number of data that request i use this channel to transmit at this timeslot
    void next_timeslot();
};

#endif