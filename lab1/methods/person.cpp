#include "../headers/person.h"

using namespace Persons;

Person::Person(const std::string& s, const std::string& n, const std::string& p):
    name(n), surname(s), patronimc(p) {}

Person::Person(const Person& other)
{
    name = other.getName();
    surname = other.getSurname();
    patronimc = other.getPatronimic();
}

std::string Person::getName() const
{
    return name;
}

std::string Person::getSurname() const
{
    return surname;
}

std::string Person::getPatronimic() const
{
    return patronimc;
}

void Person::setName(std::string& n)
{
    name = n;
}

void Person::setSurname(std::string& s)
{
    surname = s;
}

void Person::setPatronimic(std::string& p)
{
    patronimc = p;
}