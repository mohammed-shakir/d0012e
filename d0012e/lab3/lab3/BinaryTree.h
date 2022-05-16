#include "Node.h"

class BinaryTree
{
public:
    Node* root;
    BinaryTree(int* arr, int size);
    Node* Insert(Node* node, int value);
    int GetBalance(Node* node);
    Node* LeftRotate(Node* x);
    Node* RightRotate(Node* y);
    int GetHeight(Node* node);
    int max(int a, int b);
    void UpdateHeight(Node* node);
};
