#ifndef STUDENTS_H
#define STUDENTS_H

#include <string>
#include <vector>
#include <stdexcept>

namespace Students
{
    class Student
    {
        std::string FIO;
        std::vector<double> grades;
        Student* next;

    public:

        Student(std::string FIO = "",
            std::vector<double> grades = {},
            Student* next = nullptr):
            FIO(std::move(FIO)), grades(std::move(grades)), next(next) {};    

        std::string getFIO() const;
        std::vector<double> getGrades() const;
        std::vector<double>& getGrdList();
        Student* getNext();

        void setFIO(std::string FIO);
        void setGrades(std::vector<double> grades);
        void setNext(Student* st);

        double findAvrGrade() const;
    };
}

#endif