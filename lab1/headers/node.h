#ifndef NODE_H
#define NODE_H

#include "person.h"

namespace Nodes
{
    class Node
    {
    public:
        // Persons::Person* person;

        Persons::Person* left;
        Persons::Person* right;
        size_t pos;
        
        Node();
        ~Node();
    };
}

#endif