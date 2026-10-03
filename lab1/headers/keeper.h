#ifndef KEEPER_H
#define KEEPER_H

#include "node.h"
#include "admin.h"
#include "teacher.h"
#include "student.h"

namespace Keeper
{
    class University
    {
        Nodes::Node* head;
        size_t size;

        Nodes::Node* merge(Nodes::Node*, Nodes::Node*);
        void split(Nodes::Node*, const std::string&, Nodes::Node**, Nodes::Node**); /* const */
        // void findHelper(Nodes::Node*, int, const std::string&, const std::string&, const std::string&, std::vector<Nodes::Node*>&);
        void removeHelper(Nodes::Node*&, int, const std::string&, const std::string& = "", const std::string& = "");
        void postOrderDelete(Nodes::Node*);

    public:
        University();
        ~University();

        const Nodes::Node* getHead() const;
        size_t getSize() const;

        void setHead(Nodes::Node*);
        void setSize(size_t);

        bool isEmpty() const;

        void saveToFile(std::ofstream&) const;
        void readFromFile(std::ifstream&);

        void addRecord(Persons::Person&/* , Nodes::Node*& */);
        std::vector<Nodes::Node*> findRecords(int, const std::string&, const std::string& = "", const std::string& = "");
        // std::vector<Nodes::Node*> findRecordsBST(int, const std::string&, const std::string& = "", const std::string& = "");
        void removeRecords(int, const std::string&, const std::string& = "", const std::string& = "");
        void recountPositions();
        void printMembers() const;
    };
}

#endif