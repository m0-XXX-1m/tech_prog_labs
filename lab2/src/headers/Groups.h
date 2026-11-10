#ifndef GROUPS_H
#define GROUPS_H

#include "Group.h"

namespace GroupsList
{
    class Groups
    {
        GroupNode::Group* first;
        GroupNode::Group* last;
        size_t size;
    
    public:
        
        Groups(GroupNode::Group* first = nullptr,
            GroupNode::Group* last = nullptr,
            size_t size = 0
        ):
        first(first), last(last), size(size) {};
        ~Groups();

        bool isEmpty() const;
        
        GroupNode::Group* getFirst();
        GroupNode::Group* getLast();
        size_t getSize() const;

        void setFirst(GroupNode::Group* group);
        void setLast(GroupNode::Group* group);
        void setSize(size_t size);
    };
}

#endif