#include <iostream>

class BSTree
{
public:
    class Node
    {
    public:
        int value;

        Node *left = nullptr;
        Node *right = nullptr;

        Node(int value)
        {
            this->value = value;
        }
    };

    Node *root = nullptr;

    ~BSTree()
    {
        if(this->root == nullptr)
            return;

        

    }

    void insertValue(int value)
    {
        insertValueInner(this->root, value);
    }
    void insertValueInner(Node *root, int value)
    {
        if (this->root == nullptr)
        {
            this->root = new Node(value);
            return;
        }

        if (root->value == value)
            return;

        if (root->value > value)
            insertValueInner(root->left, value);

        if (root->value < value)
            insertValueInner(root->right, value);
    }

    void printSorted(bool asc)
    {
        printSortedInner(root, asc);
    }
    void printSortedInner(Node *root, bool asc)
    {
        if (root == nullptr)
            return;

        printSortedInner((asc) ? root->left : root->right, asc);
        std::cout << root->value << std::endl;
        printSortedInner((asc) ? root->right : root->left, asc);
    }
};

int main()
{
    BSTree tree;

    tree.insertValue(10);
    tree.insertValue(5);
    tree.insertValue(15);
    tree.insertValue(3);
    tree.insertValue(7);
    tree.insertValue(13);

    tree.printSorted(true);

    return 0;
}