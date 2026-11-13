#include "../headers/Students.h"

using namespace Students;

std::string Student::getFIO() const { return FIO; }

std::vector<double> Student::getGrades() const { return grades; }

std::vector<double>& Student::getGrdList() { return grades; }

Student* Student::getNext() { return next; }

void Student::setFIO(std::string FIO) { this->FIO = std::move(FIO); }

void Student::setGrades(std::vector<double> grades) { this->grades = std::move(grades); }

void Student::setNext(Student* st) { next = st; }

void Student::show() const
{
    if (FIO.empty())
        throw std::runtime_error("No information about this student.");

    std::cout
        << "Surname and initials: " << FIO << '\n'
        << "Marks: ";

    for (auto it = grades.begin(); it < grades.end(); ++ it)
    {
        std::cout << *it;
        if (std::next(it) != grades.end()) std::cout << ", ";
    }

    try
    {
        std::cout
            << '\n'
            << "Average grade: " << findAvrGrade() << '\n'
            << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cout
            << e.what() << '\n'
            << std::endl;
    }
    
}

double Student::findAvrGrade() const
{
    if (grades.empty())
        throw std::runtime_error("Student has no marks!");

    double s = 0.0;
    for (double mark : grades)
        s += mark;
    
    return s / static_cast<double>(grades.size());
}