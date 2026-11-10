#include "../headers/Group.h"

using namespace GroupNode;

bool Group::isEmpty() const { return !size; }

std::string Group::getGrName() const { return grName; }

double Group::getAvrGrade() const { return avrGrade; }

std::vector<std::string> Group::getSubjects() const { return subjects; }

std::vector<std::string>& Group::getSbjList() { return subjects; }

size_t Group::getSize() const { return size; }

Students::Student* Group::getFirst() { return first; }

Students::Student* Group::getLast() { return last; }

Group* Group::getNextGroup() { return next; }

void Group::setGrName(std::string grName) { this->grName = std::move(grName); }

void Group::setAvrGrade(double avrGrade) { this->avrGrade = avrGrade; }

void Group::setSubjects(std::vector<std::string> subjects) { this->subjects = std::move(subjects); }

void Group::setSize(size_t size) { this->size = size; }

void Group::setFirst(Students::Student* st) { first = st; }

void Group::setLast(Students::Student* st) { last = st; }

void Group::setNextGr(Group* gr) { next = gr; }

Group& Group::operator+=(Students::Student* st)
{
    if (!st)
        throw std::invalid_argument("The object cannot be NULL!");

    st->setNext(nullptr);

    if (isEmpty() || st->getFIO() < first->getFIO())
    {
        st->setNext(first);
        first = st;
        if (!last) last = st;
    }
    else
    {
        Students::Student* prev = first;
        while (prev->getNext() && 
            prev->getNext()->getFIO() < st->getFIO()) prev = prev->getNext();

        st->setNext(prev->getNext());
        prev->setNext(st);
        if (!st->getNext())
            last = st;
    }

    ++ size;
    return *this;
}

Students::Student* Group::operator--()
{
    if (isEmpty())
        throw std::range_error("The group is empty!");

    Students::Student* tmp = first;
    first = first->getNext();

    if (last == tmp)
        last = nullptr;

    -- size;
    return tmp;
}

Students::Student* Group::operator--(int)
{
    if (isEmpty())
        throw std::range_error("The group is empty!");

    Students::Student* prev = first;
    while (prev->getNext() &&
        prev->getNext() != last) prev = prev->getNext();

    if (getSize() == 1)
    {
        first = last = nullptr;
    }
    else
    {
        Students::Student* tmp = prev->getNext();
        prev->setNext(nullptr);
        last = prev;
        prev = tmp;
    }

    -- size;
    return prev;
}

void Group::showAll()
{
    if (isEmpty())
        throw std::runtime_error("The group is empty!");

    std::cout
        << "Group: " << grName << '\n';

    Students::Student* tmp = first;
    while (tmp)
    {
        std::cout
            << "Surname and initials" << tmp->getFIO() << '\n'
            << "Marks: ";

        std::vector<double>& sbj = tmp->getGrdList();
        for (auto it = sbj.begin(); it != sbj.end(); ++ it)
        {
            std::cout << *it;
            if (std::next(it) != sbj.end()) std::cout << ", ";
        }
        std::cout << '\n';

        try
        {
            std::cout
                << "Average grade: " << tmp->findAvrGrade() << '\n' << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr 
                << "Student: " << tmp->getFIO() << '\n'
                << e.what() << '\n' << std::endl;
        }
        
        tmp = tmp->getNext();
    }
}

void Group::showAvrGrdFiltered(double ag)
{
    if (isEmpty())
        throw std::runtime_error("The group is empty!");

    std::cout
        << "Group: " << grName << '\n' << '\n';

    Students::Student* tmp = first;
    while (tmp)
    {
        try
        {
            double currAg = tmp->findAvrGrade();
            if (currAg > ag)
            {
                std::cout
                    << "Surname and initials: " << tmp->getFIO() << '\n'
                    << "Average grade: " << currAg << '\n' <<  std::endl;
            }
        }
        catch (const std::exception& e)
        {
            std::cerr 
                << "Student: " << tmp->getFIO() << '\n'
                << e.what() << '\n' << std::endl;
        }

        tmp = tmp->getNext();
    }
}

Group::~Group()
{
    if (isEmpty()) return;

    Students::Student* tmp = first;
    while (first)
    {
        tmp = first->getNext();
        delete first;
        first = tmp;
    }
}