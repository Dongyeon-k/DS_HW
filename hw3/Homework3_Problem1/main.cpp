#include <iostream>

#include "functions.hpp"

int main() {
    MaxHeap heap;

    heap.enqueue(30);
    heap.enqueue(10);
    heap.enqueue(100);
    heap.enqueue(40);
    heap.enqueue(50);
    std::cout << heap.top() << std::endl;  // 100
    heap.print();                          // 100 50 30 10 40

    heap.dequeue();
    std::cout << heap.top() << std::endl;  // 50
    heap.print();                          // 50 40 30 10

    return 0;
}
