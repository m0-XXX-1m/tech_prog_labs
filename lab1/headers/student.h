#ifndef STUDENT_H
#define STUDENT_H

#include "keeper.h"

namespace Student
{
    class Student : public Person::Person
    {
        std::string group;
        std::string spec;
        unsigned int course;
        double averageGrade;

    public:
        Student(const std::string& s = "-", const std::string& n = "-", const std::string& p = "-",
            const std::string& g = "-", const std::string& spec = "-", unsigned int c = 0, double ag = -1);
        ~Student() = default;

        std::string& getGroup() const;
        std::string& getSpec() const;
        unsigned int getCourse() const;
        double getAvrGr() const;

        void setGroup(std::string&);
        void setSpec(std::string&);
        void setCourse(unsigned int);
        void setAvrGr(double);

        void saveToFile(std::ofstream&) const override;
        void readDataFromFile(std::ifstream&) override;
        void printData() const override;
    };
}

#endif