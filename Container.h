#ifndef CONTAINER_H
#define CONTAINER_H
#include <iostream>
#include <map>
#include <cassert>
using namespace std;

template <class T>
class Container{
    map<int, T> m_list;
    int m_size;
public:
    Container(){
        m_size = 0;
    }
    void insert(int id, T ele){
        assert(m_list.find(id) == m_list.end());
        m_list[id] = ele;
        m_size += 1;
    }
    T get(int id){
        assert(m_list.find(id) != m_list.end());
        return m_list[id];
    }
    int getN(){
        return m_size;
    }
};

#endif