#ifndef NODE_H
#define NODE_H

#include "person.h"

namespace Node
{
    class Node
    {
    public:
        // Person::Person* person;

        Person::Person* left;
        Person::Person* right;
        size_t pos;
        
        Node();
        ~Node();
    };
}

#endif