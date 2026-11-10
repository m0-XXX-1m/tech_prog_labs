#ifndef GROUP_H
#define GROUP_H

#include "Students.h"
#include <iostream>

namespace GroupNode
{
    class Group
    {
        std::string grName;
        double avrGrade;
        std::vector<std::string> subjects;
        size_t size;

        Students::Student* first;
        Students::Student* last;
        Group* next;
        
    public:

        Group(std::string grName = "",
            double avrGrade = 0,
            std::vector<std::string> subjects = {},
            Students::Student* first = nullptr,
            Students::Student* last = nullptr,
            Group* next = nullptr
        ):
        grName(std::move(grName)), avrGrade(std::move(avrGrade)), subjects(std::move(subjects)),
        first(first), last(last), next(next) {};
        ~Group();

        bool isEmpty() const;

        std::string getGrName() const;
        double getAvrGrade() const;
        std::vector<std::string> getSubjects() const;
        std::vector<std::string>& getSbjList();
        size_t getSize() const;

        Students::Student* getFirst();
        Students::Student* getLast();
        Group* getNextGroup();

        Group& operator+=(Students::Student* st);
        Students::Student* operator--();
        Students::Student* operator--(int);

        void setGrName(std::string grName);
        void setAvrGrade(double avrGrade);
        void setSubjects(std::vector<std::string> subjects);
        void setSize(size_t size);

        void setFirst(Students::Student* st);
        void setLast(Students::Student* st);
        void setNextGr(Group* gr);

        void showAll();
        void showAvrGrdFiltered(double ag);
    };
}

#endif