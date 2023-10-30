#pragma once
#include <vector>
#include <memory>

class Node
{
  private:
    std::vector<int> m_keys;
    std::vector<std::shared_ptr<Node>> m_children;
    bool m_leaf;

  public:
    Node(bool leaf = 0);

    friend class BTree;
};

class BTree
{
  private:
    std::shared_ptr<Node> m_root;
    int m_n;

    void print(std::shared_ptr<Node> root, int height);

  public:
    BTree(int n);

    bool search(int number);
    void add(int number);
    void split_child(std::shared_ptr<Node> root, int index);
    void add_non_full(std::shared_ptr<Node> root, int number);

    void print();
};
