#include "iostream"
#include "fstream"
#include "BinaryTree.h"

using namespace std;

void RandomArr(int* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 100 + 1;
    }
}

void PrintArr(int* arr, int size, string Header)
{
    cout << Header << ": \n [";
    for (int i = 0; i < size; i++)
    {
        cout << arr[i];
        if (i + 1 != size)
        {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

void preOrder(Node* root)
{
    if (root != NULL)
    {
        cout << root->NodeValue << " ";
        preOrder(root->LeftNode);
        preOrder(root->RightNode);
    }
}

static void _tree_print_dot_subtree(int parent_number, Node* parent, int number, Node* node, ofstream& dot_file)
{
    if (node != nullptr) {
        dot_file << "x" << number << " [label=<" << node->NodeValue << ">]" << ";\n";
        if (parent != nullptr)
            dot_file << "x" << parent_number << " -> " << "x" << number << ";\n";
        // dive into left and right subtree
        _tree_print_dot_subtree(number, node, 2 * number + 1, node->LeftNode, dot_file);
        _tree_print_dot_subtree(number, node, 2 * number + 2, node->RightNode, dot_file);
    }
    else {
        dot_file << "nil" << number << " [label=nil,fontcolor=gray,shape=none]" << ";\n";
        dot_file << "x" << parent_number << " -> " << " nil" << number << ";\n";
    }
}

void tree_print_dot(Node* root)
{
    ofstream dot_file;
    dot_file.open("lab3.dot");
    dot_file << "digraph tree1 {\n";
    if (root != nullptr)
        _tree_print_dot_subtree(-1, nullptr, 0, root, dot_file);
    dot_file << "}\n";
    dot_file.close();
    system("cd .. && dot -Tpng lab3/lab3.dot -o binarytree.png");
}

int main() {
    const int size = 51;
    int* lst_of_numbers = new int[size];
    RandomArr(lst_of_numbers, size);
    //PrintArr(lst_of_numbers, size, "Intial array: ");
    //int arr[] = { 20, 30, 40, 50, 25 };
    BinaryTree* tree = new BinaryTree(lst_of_numbers, size);
    /*if (tree->isBalanced())
        cout << "Tree is balanced";
    else
        cout << "Tree is not balanced";*/
    tree_print_dot(tree->root);
    return 0;
}