class Node {
   public:
    int val;
    bool is_red;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(int val, bool is_red) : val(val), is_red(is_red) {}
};

bool validateRedBlackTree(Node* root);
