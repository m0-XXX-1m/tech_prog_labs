#include "../headers/Groups.h"

using namespace GroupsList;

GroupNode::Group* Groups::getFirst() { return first; }

GroupNode::Group* Groups::getLast() { return last; }

size_t Groups::getSize() const { return size; }

bool Groups::isEmpty() const { return !size; }

void Groups::setFirst(GroupNode::Group* g) { first = g; }

void Groups::setLast(GroupNode::Group* g) { last = g; }

void Groups::setSize(size_t s) { size = s; }

void Groups::addGroup(const std::string& gn, const std::vector<std::string>& s)
{
    GroupNode::Group* g = new GroupNode::Group(gn, s);

    if (isEmpty() || gn < first->getGrName())
    {
        g->setNextGr(first);
        first = g;
        if (!last) last = g;
    }
    else
    {
        if (first->getGrName() == gn)
        {
            delete g;
            throw std::invalid_argument("There already exists a group with the same name!");
        }

        GroupNode::Group* prev = first;
        while (prev->getNextGroup() &&
            prev->getNextGroup()->getGrName() <= gn)
        {
            if (prev->getNextGroup()->getGrName() == gn)
            {
                delete g;
                throw std::invalid_argument("There already exists a group with the same name!");
            }

            prev = prev->getNextGroup();
        }

        g->setNextGr(prev->getNextGroup());
        prev->setNextGr(g);
        if (!g->getNextGroup())
            last = g;
    }

    ++ size;
}

GroupNode::Group* Groups::operator--()
{
    if (isEmpty())
        throw std::range_error("There is no groups!");

    GroupNode::Group* tmp = first;
    first = first->getNextGroup();

    if (last == tmp)
        last = nullptr;

    tmp->setNextGr(nullptr);
    -- size;
    return tmp;
}

GroupNode::Group* Groups::operator--(int)
{
    if (isEmpty())
        throw std::range_error("There is no groups!");

    GroupNode::Group* prev = first;
    while (prev->getNextGroup() &&
        prev->getNextGroup() != last) prev = prev->getNextGroup();

    GroupNode::Group* remove = last;
    if (getSize() == 1)
    {
        first = last = nullptr;
    }
    else
    {
        last = prev;
        prev->setNextGr(nullptr);
    }

    -- size;
    return remove;
}

GroupNode::Group* Groups::removeGroup(const std::string& gn)
{
    if (isEmpty())
        throw std::range_error("There is no groups!");

    GroupNode::Group* prev = first;
    bool found = false;
    while (prev->getNextGroup()) 
    {
        if (prev->getNextGroup()->getGrName() == gn)
        {
            found = true;
            break;
        }
        prev = prev->getNextGroup();
    }

    GroupNode::Group* remove;
    if (found)
    {
        remove = prev->getNextGroup();
        prev->setNextGr(remove->getNextGroup());

        if (last == remove)
            last = prev;
    }
    else
    {
        if (prev == first)
        {
            if (prev->getGrName() != gn)
                throw std::invalid_argument("No group exists with such name");

            remove = first;
            first = remove->getNextGroup();

            if (last == remove)
                last = nullptr;
        }
        else
        {
            throw std::invalid_argument("No group exists with such name");
        }
    }

    remove->setNextGr(nullptr);
    -- size;
    return remove;
}

GroupNode::Group* Groups::findGroup(const std::string& gn)
{
    GroupNode::Group* tmp = first;
    while (tmp &&
        tmp->getGrName() != gn) tmp = tmp->getNextGroup();

    return tmp;
}

void Groups::findStudent(const std::string& gn, const std::string& fn)
{
    if (isEmpty())
        throw std::range_error("There is no groups!");

    GroupNode::Group* tmp = findGroup(gn);

    if (!tmp)
        throw std::invalid_argument("No group exists with such name");

    try
    {
        std::vector<Students::Student*> list = tmp->find(fn);
        for (auto elem : list)
        {
            elem->show();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }    
}

void Groups::showAll()
{
    if (isEmpty())
        throw std::range_error("There is no groups!");

    GroupNode::Group* g = first;
    while (g)
    {
        try
        {
            g->showAll();
            std::cout << '\n';
        }
        catch(const std::exception& e)
        {
            std::cerr
                << e.what() << '\n'
                << std::endl;
        }
        g = g->getNextGroup();
    }
}

Groups::~Groups()
{
    if (isEmpty())
        return;

    GroupNode::Group* g = first;
    while (g)
    {
        first = first->getNextGroup();
        delete g;
        g = first;
    }
}