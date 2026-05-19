#include "functions.hpp"

#include <iostream>
#include <queue>
#include <stdexcept>

static Node *getNodeByIndex(Node *root, int index)
{
    if (!root || index < 1)
        return nullptr;

    int highestBit = 1;
    while (highestBit <= index / 2)
        highestBit *= 2;

    Node *cur = root;
    for (int bit = highestBit / 2; bit > 0 && cur; bit /= 2)
    {
        if (index & bit)
        {
            cur = cur->right;
        }
        else
        {
            cur = cur->left;
        }
    }
    return cur;
}

void MaxHeap::enqueue(int val)
{
    Node *node = new Node(val);

    if (!root)
    {
        root = node;
        last = node;
        size_ = 1;
        return;
    }

    int newIndex = size_ + 1;
    Node *parent = getNodeByIndex(root, newIndex / 2);
    node->parent = parent;

    if (newIndex % 2 == 0)
    {
        parent->left = node;
    }
    else
    {
        parent->right = node;
    }

    last = node;
    size_++;

    Node *cur = node;
    while (cur->parent && cur->val > cur->parent->val)
    {
        int temp = cur->val;
        cur->val = cur->parent->val;
        cur->parent->val = temp;
        cur = cur->parent;
    }
}

void MaxHeap::dequeue()
{
    if (!root)
        return;

    if (size_ == 1)
    {
        delete root;
        root = nullptr;
        last = nullptr;
        size_ = 0;
        return;
    }

    root->val = last->val;

    Node *oldLast = last;
    Node *parent = oldLast->parent;
    if (parent->left == oldLast)
    {
        parent->left = nullptr;
    }
    else
    {
        parent->right = nullptr;
    }

    size_--;
    last = getNodeByIndex(root, size_);
    delete oldLast;

    Node *cur = root;
    while (cur)
    {
        Node *largerChild = cur->left;
        if (cur->right && (!largerChild || cur->right->val > largerChild->val))
        {
            largerChild = cur->right;
        }

        if (!largerChild || cur->val >= largerChild->val)
            break;

        int temp = cur->val;
        cur->val = largerChild->val;
        largerChild->val = temp;
        cur = largerChild;
    }
}

int MaxHeap::top()
{
    if (!root)
        throw std::runtime_error("top() called on an empty heap.");
    return root->val;
}

int MaxHeap::size() { return size_; }

void MaxHeap::print()
{
    if (!root)
        return;
    std::queue<Node *> q;
    q.push(root);
    while (!q.empty())
    {
        std::cout << q.front()->val << " ";
        if (q.front()->left)
            q.push(q.front()->left);
        if (q.front()->right)
            q.push(q.front()->right);
        q.pop();
    }
    std::cout << std::endl;
}
