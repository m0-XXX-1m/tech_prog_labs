#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <fstream>
#include <vector>

namespace Person
{
    class Person
    {
        std::string name;
        std::string surname;
        std::string patronimc;

    public:
        Person(const std::string& s = "-", const std::string& n = "-", const std::string& p = "-");
        Person(const Person&);
        virtual ~Person();

        std::string& getName() const;
        std::string& getSurname() const;
        std::string& getPatronimic() const;

        void setName(std::string&);
        void setSurname(std::string&);
        void setPatronimic(std::string&);

        virtual void saveToFile(std::ofstream&) const = 0;
        virtual void readDataFromFile(std::ifstream&) = 0;
        virtual void printData() const = 0;
    };
}

#endif