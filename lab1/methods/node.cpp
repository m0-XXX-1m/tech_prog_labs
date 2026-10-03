#include "../headers/node.h"

using namespace Nodes;

Node::Node(): data(nullptr), left(nullptr), right(nullptr), pos(0) {}

Node::Node(Persons::Person& p): data(&p), left(nullptr), right(nullptr), pos(0) {}