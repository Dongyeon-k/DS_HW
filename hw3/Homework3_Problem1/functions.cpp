#include "functions.hpp"

#include <iostream>
#include <queue>
#include <stdexcept>

void MaxHeap::enqueue(int val) {}

void MaxHeap::dequeue() {}

int MaxHeap::top() {
    if (!root) throw std::runtime_error("top() called on an empty heap.");
    return root->val;
}

int MaxHeap::size() { return size_; }

void MaxHeap::print() {
    if (!root) return;
    std::queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        std::cout << q.front()->val << " ";
        if (q.front()->left) q.push(q.front()->left);
        if (q.front()->right) q.push(q.front()->right);
        q.pop();
    }
    std::cout << std::endl;
}
