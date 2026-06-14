#include "functions.hpp"

#include <climits>

namespace {

int blackHeight(Node* node, long long low, long long high) {
    if (node == nullptr) {
        return 1;
    }

    if (node->val <= low || node->val >= high) {
        return -1;
    }

    if (node->is_red) {
        const bool redLeft = node->left != nullptr && node->left->is_red;
        const bool redRight = node->right != nullptr && node->right->is_red;
        if (redLeft || redRight) {
            return -1;
        }
    }

    const int left = blackHeight(node->left, low, node->val);
    const int right = blackHeight(node->right, node->val, high);
    if (left == -1 || right == -1 || left != right) {
        return -1;
    }

    return left + (node->is_red ? 0 : 1);
}

}  // namespace

bool validateRedBlackTree(Node* root) {
    if (root == nullptr) {
        return true;
    }
    if (root->is_red) {
        return false;
    }

    return blackHeight(root, LLONG_MIN, LLONG_MAX) != -1;
}
