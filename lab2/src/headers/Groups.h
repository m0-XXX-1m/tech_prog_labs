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

        void addGroup(const std::string& grName,
            const std::vector<std::string>& subjects = {});
        GroupNode::Group* operator--();
        GroupNode::Group* operator--(int);
        GroupNode::Group* removeGroup(const std::string& grName);

        GroupNode::Group* findGroup(const std::string& grName);
        void findStudent(const std::string& grName, const std::string& fullName);
        void showAll();
    };
}

#endif