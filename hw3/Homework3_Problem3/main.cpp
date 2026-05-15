#include <iostream>

#include "functions.hpp"

int main() {
    Node* root = new Node(5, false);
    std::cout << validateRedBlackTree(root) << std::endl;  // 1
    delete root;
    return 0;
}
