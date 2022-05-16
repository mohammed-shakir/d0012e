#include "BinaryTree.h"

BinaryTree::BinaryTree(int* arr, int size)
{
    this->root = nullptr;
    for (int i = 0; i < size; i++)
    {
        this->root = Insert(root, arr[i]);
    }
}

Node* BinaryTree::Insert(Node* node, int value)
{
    if (node == nullptr)
    {
        return (new Node(value));
    }

    if (value < node->NodeValue)
    {
        node->LeftNode = Insert(node->LeftNode, value);
    }
    else if (value > node->NodeValue)
    {
        node->RightNode = Insert(node->RightNode, value);
    }
    else
    {
        return node;
    }

    UpdateHeight(node);

    int BalanceFactor = GetBalance(node);

    //if left is bigger and the value less
    if (BalanceFactor > 1 && value < node->LeftNode->NodeValue)
    {
        return RightRotate(node);
    }

    //if right is bigger and value is bigger
    if (BalanceFactor < -1 && value > node->RightNode->NodeValue)
    {
        return LeftRotate(node);
    }

    //if left is bigger and the value is bigger
    if (BalanceFactor > 1 && value > node->LeftNode->NodeValue)
    {
        node->LeftNode = LeftRotate(node->LeftNode);
        return RightRotate(node);
    }

    //if right is bigger and value is less
    if (BalanceFactor < -1 && value < node->RightNode->NodeValue)
    {
        node->RightNode = RightRotate(node->RightNode);
        return LeftRotate(node);
    }

    return node;
}

int BinaryTree::GetBalance(Node* node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return GetHeight(node->LeftNode) - GetHeight(node->RightNode);
}

int BinaryTree::max(int a, int b)
{
	return (a > b) ? a : b;
}


/*
     y                               x
    / \     Right Rotation          /  \
   x   T3   - - - - - - - >        T1   y
  / \       < - - - - - - -            / \
 T1  T2     Left Rotation            T2  T3

*/

Node* BinaryTree::RightRotate(Node* y)
{
    Node* x = y->LeftNode;
    Node* T2 = x->RightNode;

    x->RightNode = y;
    y->LeftNode = T2;

    UpdateHeight(x);

    UpdateHeight(y);

    return x;
}

Node* BinaryTree::LeftRotate(Node* x)
{
    Node* y = x->RightNode;
    Node* T2 = y->LeftNode;

    y->LeftNode = x;
    x->RightNode = T2;

    UpdateHeight(x);

    UpdateHeight(y);

    return y;
}

int BinaryTree::GetHeight(Node* node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return node->height;
}

void BinaryTree::UpdateHeight(Node* node)
{
    node->height = max(GetHeight(node->LeftNode), GetHeight(node->RightNode)) + 1;
}