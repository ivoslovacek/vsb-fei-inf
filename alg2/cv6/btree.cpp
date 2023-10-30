#include "btree.hpp"
#include <iostream>
#include <iterator>
#include <memory>

Node::Node(bool leaf)
{
    this->m_leaf = leaf;
}

BTree::BTree(int n)
{
    this->m_root = std::make_shared<Node>(true);
    this->m_n = n;
}

bool BTree::search(int number)
{
    std::shared_ptr<Node> root = this->m_root;

    for (int i = 0; i < root->m_keys.size(); i++)
    {
        if (number == root->m_keys[i])
        {
            return true;
        }

        if (number < root->m_keys[i] && root->m_children.size() > i)
        {
            root = root->m_children[i];
            i = 0;
        }
        else if (i == root->m_keys.size() - 1)
        {
            root = root->m_children[root->m_children.size() - 1];
            i = 0;
        }
    }

    return false;
}

void BTree::add(int number)
{
    std::shared_ptr<Node> root = this->m_root;

    std::cout << "Adding " << number << std::endl;

    if (this->m_root->m_keys.size() == 2 * this->m_n)
    {
        std::shared_ptr<Node> new_root = std::make_shared<Node>();
        this->m_root = new_root;

        new_root->m_children.insert(new_root->m_children.begin(), root);

        new_root->m_children[0]->m_keys.push_back(number);

        this->split_child(new_root, 0);
        this->add_non_full(new_root, number);
    }
    else
    {
        this->add_non_full(root, number);
    }
}

void BTree::add_non_full(std::shared_ptr<Node> root, int number)
{
    if (root->m_keys.size() == 0)
    {
        root->m_keys.push_back(number);
        return;
    }

    if (root->m_leaf)
    {
        root->m_keys.push_back(root->m_keys.back());

        auto it = std::prev(root->m_keys.rend());
        for (; it != root->m_keys.rbegin() && number < *it; it++)
        {
            *std::prev(it) = *it;
        }

        *std::prev(it) = number;
    }
    else
    {
        int i = root->m_keys.size() - 1;

        while (i >= 0 && number < root->m_keys[i])
        {
            i--;
        }

        std::cout << "child index" << i << std::endl;

        if (i >= 0)
        {
            if (root->m_children[i]->m_keys.size() == 2 * this->m_n)
            {
                this->split_child(root, i);

                if (number > root->m_keys[i])
                {
                    i++;
                }
            }

            this->add_non_full(root->m_children[i], number);
        }
    }
}

void BTree::split_child(std::shared_ptr<Node> root, int index)
{
    std::shared_ptr<Node> child = root->m_children[index];

    for (auto each : child->m_keys)
    {
        std::cout << "Key: " << each << std::endl;
    }

    std::shared_ptr<Node> new_child = std::make_shared<Node>(child->m_leaf);
    root->m_children.push_back(new_child);

    {
        auto half_it = child->m_keys.begin();
        std::advance(half_it, child->m_keys.size() / 2);

        root->m_keys.insert(root->m_keys.begin() + index, *half_it);

        new_child->m_keys = std::vector<int>(half_it, child->m_keys.end());
        child->m_keys.erase(half_it, child->m_keys.end());
    }

    if (!child->m_leaf)
    {
        {
            auto half_it = child->m_children.begin();
            std::advance(half_it, child->m_children.size() / 2);

            child->m_children = std::vector<std::shared_ptr<Node>>(half_it, child->m_children.end());
            new_child->m_children.erase(half_it, child->m_children.end());
        }
    }
}

void BTree::print()
{
    int height = 0;

    for (int i = 0; i < this->m_root->m_keys.size(); i++)
    {
        std::cout << "Height " << height << std::endl;
        std::cout << this->m_root->m_keys[i] << std::endl;
        if (i < this->m_root->m_children.size())
        {
            this->print(this->m_root->m_children[i], height + 1);
        }
    }

    if (this->m_root->m_children.size() > 1)
    {
        print(this->m_root->m_children[this->m_root->m_children.size() - 1], 1);
    }
}

void BTree::print(std::shared_ptr<Node> root, int height)
{
    for (int i = 0; i < this->m_root->m_keys.size(); i++)
    {
        std::cout << "Height " << height << std::endl;
        std::cout << root->m_keys[i] << std::endl;
        if (i < root->m_children.size())
        {
            this->print(root->m_children[i], height + 1);
        }
    }

    if (root->m_children.size() > 1)
    {
        print(root->m_children[root->m_children.size() - 1], 1);
    }
}
