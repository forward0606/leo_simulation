#include <iostream>

#include "Node.h"

int main(){
    Node a(0, Node::SATELLITE, 10000);
    User b(1);
    for(int i=0;i<Node::NodeList.getN();i++){
        Node *p = Node::NodeList.get(i);
        cout<<p->getId()<<" "<<p->get_type()<<'\n';
    }

    return 0;
}