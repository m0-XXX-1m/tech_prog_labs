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

    tmp->setNext(nullptr);
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
        throw std::range_error("The group is empty!");

    findAvrGrade();

    std::cout
        << "Group name: " << grName << '\n'
        << "Group average grade: " << avrGrade << '\n'
        << "Subjects: ";

    for (auto it = subjects.begin(); it < subjects.end(); ++ it)
    {
        std::cout << *it;
        if (std::next(it) != subjects.end()) std::cout << ", ";
    }
    std::cout << '\n';

    Students::Student* tmp = first;
    while (tmp)
    {
        try
        {
            tmp->show();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
        tmp = tmp->getNext();
    }
}

void Group::showAvrGrdFiltered(double ag)
{
    if (isEmpty())
        throw std::range_error("The group is empty!");

    findAvrGrade();

    std::cout
        << "Group name: " << grName << '\n'
        << "Group average grade: " << avrGrade << '\n'
        << "Subjects: ";

    for (auto it = subjects.begin(); it < subjects.end(); ++ it)
    {
        std::cout << *it;
        if (std::next(it) != subjects.end()) std::cout << ", ";
    }
    std::cout << '\n';
    
    Students::Student* tmp = first;
    while (tmp)
    {
        try
        {
            if (tmp->findAvrGrade() >= ag)
                tmp->show();
        }
        catch(const std::exception& e) {}

        tmp = tmp->getNext();
    }
}

std::vector<Students::Student*> Group::find(const std::string& fn)
{
    if (isEmpty())
        throw std::range_error("The group is empty!");

    std::vector<Students::Student*> res;
    Students::Student* tmp = first;
    while (tmp) 
    {
        if (tmp->getFIO() == fn) res.push_back(tmp);
        tmp = tmp->getNext();
    }
    

    if (res.empty())
        throw std::invalid_argument("No such student in the group.");
    
    return res;
}

void Group::findAvrGrade()
{
    if (isEmpty())
        throw std::range_error("The group is empty!");

    double s = 0.0;
    int num = 0;
    Students::Student* tmp = first;
    while (tmp)
    {
        try
        {
            s += tmp->findAvrGrade();
            ++ num;
        }
        catch(const std::exception& e)
        {}
        tmp = tmp->getNext();
    }

    if (num)
        avrGrade = s / static_cast<double>(num);
    else
        avrGrade = 0.0;
}

Group::~Group()
{
    if (isEmpty()) return;

    Students::Student* tmp = first;
    while (tmp)
    {
        first = first->getNext();
        delete tmp;
        tmp = first;
    }
}