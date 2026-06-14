class Node
{
public:
    int val;
    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;

    Node(int val) : val(val) {}
};

class MaxHeap
{
public:
    void enqueue(int val);
    void dequeue();

    int top();
    int size();

    void print(); /* not graded */

private:
    Node *root = nullptr;
    Node *last = nullptr;
    int size_ = 0;
};
