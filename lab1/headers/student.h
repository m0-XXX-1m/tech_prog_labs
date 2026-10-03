#ifndef STUDENT_H
#define STUDENT_H

#include "person.h"

namespace Students
{
    class Student : public Persons::Person
    {
        std::string group;
        std::string spec;
        unsigned int course;
        double averageGrade;

    public:
        Student(const std::string& = "-", const std::string& = "-", const std::string& = "-",
            const std::string& = "-", const std::string& = "-", unsigned int = 0, double = -1);
        ~Student() = default;

        std::string getGroup() const;
        std::string getSpec() const;
        unsigned int getCourse() const;
        double getAvrGr() const;
        int getRoleRank() const override;

        void setGroup(std::string&);
        void setSpec(std::string&);
        void setCourse(unsigned int);
        void setAvrGr(double);
        void setAvrGr(int*, size_t);

        void saveToFile(std::ofstream&) const override;
        void readDataFromFile(std::ifstream&) override;
        void printData() const override;
    };
}

#endif