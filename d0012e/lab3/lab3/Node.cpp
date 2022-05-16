#include "Node.h"

Node::Node(int NodeValue)
{
    this->LeftNode = nullptr;
    this->RightNode = nullptr;
    this->NodeValue = NodeValue;
    this->height = 1;
}