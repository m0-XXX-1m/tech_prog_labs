#include "../headers/keeper.h"

/* #define ADMIN 1
#define TEACHER 2
#define STUDENT 3 */

using namespace Keeper;

class QueueNode
{
public:
    QueueNode* next;
    Nodes::Node* node;

    QueueNode(Nodes::Node* n): next(nullptr), node(n) {};
    ~QueueNode() = default;
};

class Queue
{
public:
    QueueNode* first;
    QueueNode* last;
    size_t s;

    Queue(): first(nullptr), last(nullptr), s(0) {};
    ~Queue();

    void push(Nodes::Node*);
    Nodes::Node* removeFirst();
};

Queue::~Queue()
{
    QueueNode* tmp = first;
    while (tmp)
    {
        tmp = tmp->next;
        delete first;
        first = tmp;
    }
}

void Queue::push(Nodes::Node* n)
{
    if (!n) throw std::invalid_argument("Cannot to push NULL elemet");

    QueueNode* qn = new QueueNode(n);
    if (!first)
    {
        first = last = qn;
    }
    else
    {
        last->next = qn;
        last = qn;
    }
    ++ s;
}

Nodes::Node* Queue::removeFirst()
{
    if (!first) throw std::out_of_range("Queue is empty");

    if (first == last) last = nullptr;

    QueueNode* qn = first;
    Nodes::Node* res = qn->node;

    first = first->next;
    qn->next = nullptr;
    -- s;
    delete qn;

    return res;
}

void University::postOrderDelete(Nodes::Node* h)
{
    if (!h) return;

    postOrderDelete(h->left);
    postOrderDelete(h->right);

    delete h;
}

University::University(): head(nullptr), size(0) {}

University::~University()
{
    postOrderDelete(head);
    head = nullptr;
    size = 0;
}

Nodes::Node* University::getHead()
{
    return head;
}

size_t University::getSize() const
{
    return size;
}

void University::setHead(Nodes::Node* h)
{
    head = h;
}

void University::setSize(size_t s)
{
    size = s;
}

bool University::isEmpty() const
{
    return !size;
}

void University::recountPositions()
{
    if (isEmpty())
    {
        return;
    }

    Queue* q = new Queue;
    q->push(head);

    int pos = 1;
    while (q->s)
    {
        Nodes::Node* n = q->removeFirst();
        n->pos = pos;
        ++ pos;

        if (n->left) q->push(n->left);
        if (n->right) q->push(n->right);
    }

    delete q;
}

Nodes::Node* University::merge(Nodes::Node* l, Nodes::Node* r)
{
    if (!l) return r;
    if (!r) return l;

    if (l->data->getRoleRank() < r->data->getRoleRank())
    {
        l->right = merge(l->right, r);
        return l;
    }
    else
    {
        r->left = merge(l, r->left);
        return r;
    }
}

void University::split(Nodes::Node* cur, const std::string& s, Nodes::Node** lftSubTr, Nodes::Node** rghtSubTr)
{
    if (!cur)
    {
        *lftSubTr = nullptr;
        *rghtSubTr = nullptr;
        return;
    }

    if (cur->data->getSurname() < s)
    {
        split(cur->right, s, &cur->right, rghtSubTr);
        *lftSubTr = cur;
    }
    else
    {
        split(cur->left, s, lftSubTr, &cur->left);
        *rghtSubTr = cur;
    }
}

void University::addRecord(Persons::Person& p/* , Nodes::Node*& n */)
{
    /* if (!n)
    {
        n = new Nodes::Node(p);
        // if (n == head) n->pos = 1;
        ++ size;
        return;
    }

    int curNodeRole = n->data->getRoleRank();
    int persRole = p.getRoleRank();

    if (persRole >= curNodeRole)
    {
        if (p.getSurname() >= n->data->getSurname())
        {
            addRecord(p, n->right);
        }
        else
        {
            addRecord(p, n->left);
        }
    }
    else
    {
        Nodes::Node* nw = new Nodes::Node(p);
        split(n, p.getSurname(), &nw->left, &nw->right);

        n = nw;
        ++ size;
    } */

    /* if (!n)
    {
        n = new Nodes::Node(p);
        ++size;
        return;
    }

    if (p.getRoleRank() < n->data->getRoleRank())
    {
        Nodes::Node* nw = new Nodes::Node(p);
        split(n, p.getSurname(), &nw->left, &nw->right);
        n = nw;
        ++size;
        return;
    }

    if (p.getSurname() < n->data->getSurname())
        addRecord(p, n->left);
    else
        addRecord(p, n->right); */

    Nodes::Node* l = nullptr;
    Nodes::Node* r = nullptr;
    split(head, p.getSurname(), &l, &r);

    Nodes::Node* m = new Nodes::Node(p);
    head = merge(merge(l, m), r);

    ++size;
    recountPositions();
}

std::vector<Nodes::Node*> University::findRecords(int rank, const std::string& s, const std::string& n, const std::string& p)
{
    if (isEmpty()) return {};

    Queue* q = new Queue;
    q->push(head);

    std::vector<Nodes::Node*> res;
    while (q->s)
    {
        Nodes::Node* node = q->removeFirst();
        if (rank == node->data->getRoleRank() &&
            s == node->data->getSurname())
        {
            if (!n.empty())
            {
                if (n == node->data->getName()) res.push_back(node);
            }
            else if (!p.empty())
            {
                if (n == node->data->getName() && p == node->data->getPatronimic()) res.push_back(node);
            }
            else
            {
                res.push_back(node);
            }
        }

        if (node->left) q->push(node->left);
        if (node->right) q->push(node->right);
    }

    delete q;

    return res;
}

/* void University::findHelper(Nodes::Node* node, int rank,
    const std::string& s, const std::string& n, const std::string& p, std::vector<Nodes::Node*>& res)
{
    if (!node) return;

    if (s < node->data->getSurname())
    {
        findHelper(node->left, rank, s, n, p, res);
        return;
    }
    if (s > node->data->getSurname())
    {
        findHelper(node->right, rank, s, n, p, res);
        return;
    }

    if (rank == node->data->getRoleRank() &&
        (n.empty() || n == node->data->getName()) &&
        (p.empty() || p == node->data->getPatronimic()))
    {
        res.push_back(node);
    }

    findHelper(node->right, rank, s, n, p, res);
}

std::vector<Nodes::Node*> University::findRecordsBST(int rank, const std::string& s, const std::string& n, const std::string& p)
{
    if (isEmpty()) return {};

    std::vector<Nodes::Node*> res;
    findHelper(head, rank, s, n, p, res);

    return res;
} */

void University::removeHelper(Nodes::Node*& node, int rank, const std::string& s, const std::string& n, const std::string& p)
{
    if (!node) return;

    if (s < node->data->getSurname())
    {
        removeHelper(node->left, rank, s, n, p);
    }
    else if (s > node->data->getSurname())
    {
        removeHelper(node->right, rank, s, n, p);
    }
    else
    {
        if (rank == node->data->getRoleRank() &&
            (n.empty() || n == node->data->getName()) &&
            (p.empty() || p == node->data->getPatronimic()))
        {
            Nodes::Node* rmNode = node;
            node = merge(node->left, node->right);

            delete rmNode;

            -- size;

            removeHelper(node, rank, s, n, p);
        }
        else
        {
            removeHelper(node->left, rank, s, n, p);
            removeHelper(node->right, rank, s, n, p);
        }
    }
}

void University::removeRecords(int rank, const std::string& s, const std::string& n, const std::string& p)
{
    if (isEmpty()) throw std::out_of_range("List is empty");

    removeHelper(head, rank, s, n, p);

    recountPositions();
}

/* void University::addRecord(Persons::Person& p, Nodes::Node* n, Nodes::Node* prev)
{
    if (!head)
    {
        head = new Nodes::Node(p);
        head->pos = 1;
        ++ size;

        return;
    }
    else
    {
        if (!n) n = head;
        
        int curNodeRole = n->data->getRoleRank();
        int persRole = p.getRoleRank();

        if (persRole >= curNodeRole)
        {
            if (p.getSurname() >= n->data->getSurname())
            {
                if (!n->right)
                {
                    n->right = new Nodes::Node(p);
                    recountPosFrom(n);
                }
                else addRecord(p, n->right, n);
            }
            else
            {
                if (!n->left)
                {
                    n->left = new Nodes::Node(p);
                    recountPosFrom(n);
                }
                else addRecord(p, n->left, n);
            }
        }
        else
        {   
            Nodes::Node* nw = new Nodes::Node(p);
            if (n == head)
            {
                head = nw;
            }
            else
            {
                if (prev->right == n) prev->right = nw;
                else prev->left = nw;
            }
            
            if (p.getSurname() >= n->data->getSurname()) nw->right = n;
            else nw->left = n;

            nw->pos = n->pos;
            recountPosFrom(nw);
        }
        ++ size;
    }
} */

void University::printMembers() const
{
    if (!size) throw std::out_of_range("Storage is empty");

    Queue* q = new Queue;
    q->push(head);

    while (q->s)
    {
        Nodes::Node* n = q->removeFirst();
        std::cout << "Position:\t" << n->pos;
        n->data->printData();

        if (n->left) q->push(n->left);
        if (n->right) q->push(n->right);
    }
    delete q;
}

void University::saveToFile(std::ofstream& f) const
{
    if (!f.is_open()) throw std::runtime_error("Error while opening a file to write");

    Queue* q = new Queue;
    q->push(head);

    while (q->s)
    {
        Nodes::Node* n = q->removeFirst();
        n->data->saveToFile(f);

        if (n->left) q->push(n->left);
        if (n->right) q->push(n->right);
    }

    delete q;
}

void University::readFromFile(std::ifstream& f)
{
    if (!f.is_open()) throw std::runtime_error("Error while opening a file to read");

    std::string line;
    while (std::getline(f, line))
    {
        if (line.empty()) continue;
        if (line.back() == '\r') line.pop_back();

        if (line[0] == '#')
        {
            std::string role = line.substr(1);

            if (role == "ADMIN")
            {
                Persons::Person* a = new Admins::Admin;
                a->readDataFromFile(f);
                addRecord(*a/* , head */);
            }
            else if (role == "TEACHER")
            {
                Persons::Person* t = new Teachers::Teacher;
                t->readDataFromFile(f);
                addRecord(*t/* , head */);
            }
            else if (role == "STUDENT")
            {
                Persons::Person* s = new Students::Student;
                s->readDataFromFile(f);
                addRecord(*s/* , head */);
            }
        }
    }
}