#include "btree.hpp"
#include <filesystem>
#include <iostream>
#include <iterator>
#include <memory>
#include <algorithm>
#include <ostream>

Node::Node(std::shared_ptr<Node> parent, bool leaf)
{
    if (parent == nullptr)
    {
        this->m_parent = std::nullopt;
    }
    else
    {
        this->m_parent = parent;
    }
    this->m_leaf = leaf;
}

BTree::BTree(int n)
{
    this->m_root = nullptr;
    this->m_n = n;
}

bool BTree::search(int number, std::shared_ptr<Node> root)
{
    if (root == nullptr)
    {
        return false;
    }

    size_t i = 0;
    while (i < root->m_keys.size() && number > root->m_keys[i])
    {
        i++;
    }

    if (i < root->m_keys.size() && number == root->m_keys[i])
    {
        return true;
    }
    else
    {
        if (i >= root->m_children.size())
        {
            return false;
        }
        return this->search(number, root->m_children[i]);
    }
}

bool BTree::search(int number)
{
    return (this->m_root) ? this->search(number, this->m_root) : false;
}

void BTree::add(int number)
{
    if (this->m_root == nullptr)
    {
        this->m_root = std::make_shared<Node>(nullptr, true);
        this->m_root->m_keys.push_back(number);
    }
    else
    {
        if (this->m_root->m_keys.size() == 2 * this->m_n)
        {
            std::shared_ptr<Node> parent = std::make_shared<Node>(this->m_root);
            this->m_root->m_parent = parent;
            parent->m_children.push_back(this->m_root);
            this->m_root = parent;

            number = split_child(this->m_root, 0, number);

            this->m_root->m_keys.push_back(number);
        }
        else
        {
            this->add_non_full(this->m_root, number);
        }
    }
}

void BTree::add_non_full(std::shared_ptr<Node> root, int number)
{
    if (root->m_leaf)
    {
        root->m_keys.push_back(number);
        std::sort(root->m_keys.begin(), root->m_keys.end());
    }
    else
    {
        int i = root->m_keys.size() - 1;

        for (; i >= 0; i--)
        {
            if (number > root->m_keys[i])
            {
                break;
            }
        }
        i++;

        if (root->m_children[i]->m_keys.size() == 2 * this->m_n)
        {
            while (true)
            {
                number = split_child(root, i, number);

                root->m_keys.push_back(number);
                std::sort(root->m_keys.begin(), root->m_keys.end());

                if (root->m_keys.size() > 2 * this->m_n)
                {
                    if (!root->m_parent.has_value())
                    {
                        std::shared_ptr<Node> parent = std::make_shared<Node>();
                        root->m_parent = parent;
                        parent->m_children.push_back(root);
                        root = parent;

                        number = split_child(root, 0, number);

                        root->m_keys.push_back(number);

                        break;
                    }

                    std::shared_ptr<Node> parent = root->m_parent.value().lock();
                    if (parent->m_children.size() == 0)
                    {
                        return;
                    }

                    int i = 0;
                    for (; i < parent->m_children.size(); i++)
                    {
                        if (parent->m_children[i] == root)
                        {
                            break;
                        }
                    }

                    root = parent;

                    std::cout << root << std::endl;
                    std::cout << i;
                }
                else
                {
                    return;
                }
            }
        }
        else
        {
            add_non_full(root->m_children[i], number);
        }
    }
}

int BTree::split_child(std::shared_ptr<Node> root, int index, int number)
{
    std::shared_ptr<Node> child = root->m_children[index];
    std::shared_ptr<Node> new_child = std::make_shared<Node>(root, child->m_leaf);

    child->m_keys.push_back(number);
    std::sort(child->m_keys.begin(), child->m_keys.end());

    int half_index = child->m_keys.size() / 2;
    int half_number = child->m_keys[half_index];

    new_child->m_keys.insert(new_child->m_keys.begin(), child->m_keys.begin() + (half_index + 1), child->m_keys.end());
    child->m_keys.erase(child->m_keys.begin() + (half_index), child->m_keys.end());

    root->m_children.insert(root->m_children.begin() + (index + 1), new_child);

    if (!child->m_leaf && child->m_children.size() != 1)
    {
        new_child->m_children.insert(new_child->m_children.begin(), child->m_children.begin() + half_index,
                                     child->m_children.end());
        child->m_children.erase(child->m_children.begin() + half_index, child->m_children.end());
    }

    return half_number;
}

void BTree::print()
{
    if (this->m_root)
    {
        print(this->m_root, 0);
    }
}

void BTree::print(std::shared_ptr<Node> root, int height)
{
    if (root != nullptr)
    {
        for (int i = 0; i < root->m_keys.size(); i++)
        {
            std::cout << "Height " << height << std::endl;
            std::cout << root->m_keys[i] << std::endl;
            if (i < root->m_children.size())
            {
                this->print(root->m_children[i], height + 1);
            }
        }

        if (!root->m_children.empty() && root->m_children.size() > 1)
        {
            std::cout << "last child" << std::endl;
            this->print(root->m_children.back(), height + 1);
        }
    }
}
