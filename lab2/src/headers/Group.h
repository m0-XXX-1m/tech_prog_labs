#ifndef GROUP_H
#define GROUP_H

#include "Students.h"

namespace GroupNode
{
    class Group
    {
        std::string grName;
        std::vector<std::string> subjects;
        double avrGrade;
        size_t size;

        Students::Student* first;
        Students::Student* last;
        Group* next;
        
    public:

        Group(std::string grName = "",
            std::vector<std::string> subjects = {},
            double avrGrade = 0,
            size_t size = 0,
            Students::Student* first = nullptr,
            Students::Student* last = nullptr,
            Group* next = nullptr
        ):
        grName(std::move(grName)), subjects(std::move(subjects)), avrGrade(std::move(avrGrade)), size(size),
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

        std::vector<Students::Student*> find(const std::string& fullName);
        void findAvrGrade();
        void showAll();
        void showAvrGrdFiltered(double ag);
    };
}

#endif