#include "../headers/Students.h"

using namespace Students;

std::string Student::getFIO() const { return FIO; }

std::vector<double> Student::getGrades() const { return grades; }

std::vector<double>& Student::getGrdList() { return grades; }

Student* Student::getNext() { return next; }

void Student::setFIO(std::string FIO) { this->FIO = std::move(FIO); }

void Student::setGrades(std::vector<double> grades) { this->grades = std::move(grades); }

void Student::setNext(Student* st) { next = st; }

double Student::findAvrGrade() const
{
    if (grades.empty())
        throw std::runtime_error("Student has no marks!");
    
    double s;
    for (double mark : grades)
        s += mark;
    
    return s / grades.size();
}