#ifndef KEEPER_H
#define KEEPER_H

#include "node.h"

namespace Keeper
{
    class University
    {
        // Node::Node* first;
        // Node::Node* last;

        Node::Node* head;
        size_t size;

    public:
        University();
        ~University();

        Node::Node* getHead() const;
        size_t getSize() const;

        void setHead(Node::Node*);
        void setSize();

        bool isEmpty() const;

        void saveToFile() const;
        void readFromFile();

        void addRecord(const Person::Person&);
        // Person::Person* findRecord(const std::string& s = "", const std::string& n = "", const std::string& p = "", size_t pos);
        Node::Node* findRecord(const std::string& s = "", const std::string& n = "", const std::string& p = "", size_t pos);
        void removeRecord(const std::string& s = "", const std::string& n = "", const std::string& p = "");
        void recountPositions(Node::Node*);
    };
}

#endif