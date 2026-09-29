#ifndef KEEPER_H
#define KEEPER_H

#include "node.h"

namespace Keeper
{
    class University
    {
        // Nodes::Node* first;
        // Nodes::Node* last;

        Nodes::Node* head;
        size_t size;

    public:
        University();
        ~University();

        Nodes::Node* getHead() const;
        size_t getSize() const;

        void setHead(Nodes::Node*);
        void setSize();

        bool isEmpty() const;

        void saveToFile() const;
        void readFromFile();

        void addRecord(const Persons::Person&);
        // Person::Person* findRecord(const std::string& s = "", const std::string& n = "", const std::string& p = "", size_t pos);
        Nodes::Node* findRecord(const std::string& s = "", const std::string& n = "", const std::string& p = "", size_t pos);
        void removeRecord(const std::string& s = "", const std::string& n = "", const std::string& p = "");
        void recountPositions(Nodes::Node*);
    };
}

#endif