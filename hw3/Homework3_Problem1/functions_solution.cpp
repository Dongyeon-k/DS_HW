#include "functions.hpp"

#include <iostream>
#include <queue>
#include <stdexcept>
#include <utility>

namespace
{

    Node *nodeAt(Node *root, int index)
    {
        if (index < 1)
        {
            return nullptr;
        }

        int mask = 1;
        while (mask <= index / 2)
        {
            mask <<= 1;
        }

        Node *cur = root;
        for (mask >>= 1; mask > 0 && cur != nullptr; mask >>= 1)
        {
            cur = (index & mask) ? cur->right : cur->left;
        }
        return cur;
    }

} // namespace

void MaxHeap::enqueue(int val)
{
    Node *node = new Node(val);

    if (root == nullptr)
    {
        root = last = node;
        size_ = 1;
        return;
    }

    const int index = ++size_;
    Node *parent = nodeAt(root, index / 2);
    node->parent = parent;

    if (index % 2 == 0)
    {
        parent->left = node;
    }
    else
    {
        parent->right = node;
    }
    last = node;

    for (Node *cur = node; cur->parent != nullptr && cur->val > cur->parent->val;
         cur = cur->parent)
    {
        std::swap(cur->val, cur->parent->val);
    }
}

void MaxHeap::dequeue()
{
    if (root == nullptr)
    {
        return;
    }

    if (size_ == 1)
    {
        delete root;
        root = last = nullptr;
        size_ = 0;
        return;
    }

    root->val = last->val;
    Node *removed = last;
    Node *parent = removed->parent;

    if (parent->left == removed)
    {
        parent->left = nullptr;
    }
    else
    {
        parent->right = nullptr;
    }

    last = nodeAt(root, --size_);
    delete removed;

    for (Node *cur = root;;)
    {
        Node *child = cur->left;
        if (cur->right != nullptr &&
            (child == nullptr || cur->right->val > child->val))
        {
            child = cur->right;
        }

        if (child == nullptr || cur->val >= child->val)
        {
            break;
        }

        std::swap(cur->val, child->val);
        cur = child;
    }
}

int MaxHeap::top()
{
    if (root == nullptr)
    {
        throw std::runtime_error("top() called on an empty heap");
    }
    return root->val;
}

int MaxHeap::size()
{
    return size_;
}

void MaxHeap::print()
{
    if (root == nullptr)
    {
        return;
    }

    std::queue<Node *> q;
    q.push(root);

    while (!q.empty())
    {
        Node *cur = q.front();
        q.pop();

        std::cout << cur->val << ' ';
        if (cur->left != nullptr)
        {
            q.push(cur->left);
        }
        if (cur->right != nullptr)
        {
            q.push(cur->right);
        }
    }
    std::cout << '\n';
}
