#include <functional>
#include <iostream>
#include <string>

// Implement empty templates, classes, and required member functions.

template <class K, class V>
class TreeNode {
    private:
        K key;
        V value;
        TreeNode<K, V>* left;
        TreeNode<K, V>* right;
    public:
        TreeNode(const K& k, const V& v):key(k), value(v), left(nullptr), right(nullptr) {};

        K getKey() const{return key;}
        void setKey(const K& newKey) { key = newKey; }

        V getValue() const { return value; }
        void setValue(const V& newValue) { value = newValue; }

        TreeNode<K, V>* getLeft() const { return left; }
        void setLeft(TreeNode<K, V>* newLeft) { left = newLeft; }

        TreeNode<K, V>* getRight() const { return right; }
        void setRight(TreeNode<K, V>* newRight) { right = newRight; }
};



template <typename K, typename V, typename Compare = std::less<K>>
class CustomMap {
    private:
        TreeNode<K, V>* root;
        Compare compare;

        TreeNode<K, V>* insertNode(TreeNode<K, V>* node, const K& k, const V& v) {
            if (node == nullptr) { return new TreeNode<K, V>(k, v);}
            else if (compare(k, node->getKey())) { node->setLeft(insertNode(node->getLeft(), k, v)); }
            else if (compare(node->getKey(), k)) { node->setRight(insertNode(node->getRight(), k, v)); }
            return node;
        }

        void printNodes(TreeNode<K, V>* node){
            if (node == nullptr){ return ;}
            
            printNodes(node->getLeft());
            std::cout << node->getKey() << ":" << node->getValue()<<std::endl;
            printNodes(node->getRight());
        }

        TreeNode<K, V>* findNode(TreeNode<K, V>* node, const K& key) const {
            if (node == nullptr) return nullptr;

            if (compare(key, node->getKey())) {
                return findNode(node->getLeft(), key);
            }
            else if (compare(node->getKey(), key)) {
                return findNode(node->getRight(), key);
            }
            else {
                return node;
            }
        }

        TreeNode<K, V>* findMinNode(TreeNode<K, V>* node) const {
            if (node == nullptr) return nullptr;
            while (node->getLeft() != nullptr) {
                node = node->getLeft();
            }
            return node;
        }

        TreeNode<K, V>* deleteNode(TreeNode<K, V>* node, const K& key) {
            if (node == nullptr) return nullptr;

            if (compare(key, node->getKey())) {
                node->setLeft(deleteNode(node->getLeft(), key));
            }
            else if (compare(node->getKey(), key)) {
                node->setRight(deleteNode(node->getRight(), key));
            }
            else {
                // 자식 없음
                if (node->getLeft() == nullptr && node->getRight() == nullptr) {
                    delete node;
                    return nullptr;
                }
                // 오른쪽 자식만 있음
                else if (node->getLeft() == nullptr) {
                    TreeNode<K, V>* temp = node->getRight();
                    delete node;
                    return temp;
                }
                // 왼쪽 자식만 있음
                else if (node->getRight() == nullptr) {
                    TreeNode<K, V>* temp = node->getLeft();
                    delete node;
                    return temp;
                }
                // case 4: 자식 둘 다 있음
                else {
                    TreeNode<K, V>* right_min = findMinNode(node->getRight());
                    node->setKey(right_min->getKey());
                    node->setValue(right_min->getValue());

                    node->setRight(deleteNode(node->getRight(), right_min->getKey()));
                }
            }
            return node;
        }

    public:
        CustomMap(): root(nullptr), compare(Compare()){}
        
        Compare get_compare() const {return compare;}

        void insert(K key, V value){ root = insertNode(root, key, value); }
        void print_map(){ printNodes(root); }

        void delete_key(K key){ root = deleteNode(root, key); }

        V get_value(K key){
            TreeNode<K, V>* node = findNode(root, key);
            if (node == nullptr){ return V(); }
            else{ return node->getValue(); }
        }

        V& operator[](K key){
            TreeNode<K, V>* node = findNode(root, key);

            if (node == nullptr) {
                root = insertNode(root, key, V());
                node = findNode(root, key);
            }

            return *(new V(node->getValue())); // <- 이건 잘못된 방식
        }

};
