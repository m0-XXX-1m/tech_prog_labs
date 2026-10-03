#ifndef NODE_H
#define NODE_H

#include "person.h"

namespace Nodes
{
    class Node
    {
    public:
        Persons::Person* data;
        Node* left;
        Node* right;
        size_t pos;
        
        Node();
        Node(Persons::Person&);
        ~Node() = default;
    };
}

#endif