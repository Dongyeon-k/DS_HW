#include "functions.hpp"

#include <climits>

namespace {

int validate(Node* node, long long lower, long long upper) {
    if (node == nullptr) {
        return 1;
    }

    if (node->val <= lower || node->val >= upper) {
        return -1;
    }

    if (node->is_red) {
        if ((node->left != nullptr && node->left->is_red) ||
            (node->right != nullptr && node->right->is_red)) {
            return -1;
        }
    }

    int left_black_height = validate(node->left, lower, node->val);
    int right_black_height = validate(node->right, node->val, upper);

    if (left_black_height == -1 || right_black_height == -1 ||
        left_black_height != right_black_height) {
        return -1;
    }

    return left_black_height + (node->is_red ? 0 : 1);
}

}  // namespace

bool validateRedBlackTree(Node* root) {
    if (root == nullptr) {
        return true;
    }

    if (root->is_red) {
        return false;
    }

    return validate(root, LLONG_MIN, LLONG_MAX) != -1;
}
