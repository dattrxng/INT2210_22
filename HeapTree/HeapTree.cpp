#include <iostream>
#include <vector>

class Heap {
private:
    std::vector<int> heap;
    bool isMaxHeap;

    void swap(int &a, int &b) {
        int temp = a;
        a = b;
        b = temp;
    }

    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int largestSmallest = index;

        if (isMaxHeap) {
            if (leftChild < heap.size() && heap[leftChild] > heap[largestSmallest]) {
                largestSmallest = leftChild;
            }

            if (rightChild < heap.size() && heap[rightChild] > heap[largestSmallest]) {
                largestSmallest = rightChild;
            }
        } else {
            if (leftChild < heap.size() && heap[leftChild] < heap[largestSmallest]) {
                largestSmallest = leftChild;
            }

            if (rightChild < heap.size() && heap[rightChild] < heap[largestSmallest]) {
                largestSmallest = rightChild;
            }
        }

        if (largestSmallest != index) {
            swap(heap[index], heap[largestSmallest]);
            heapifyDown(largestSmallest);
        }
    }
)
    void heapifyUp(int index) {
        int parent = (index - 1) / 2;

        if (isMaxHeap) {
            if (index > 0 && heap[index] > heap[parent]) {
                swap(heap[index], heap[parent]);
                heapifyUp(parent);
            }
        } else {
            if (index > 0 && heap[index] < heap[parent]) {
                swap(heap[index], heap[parent]);
                heapifyUp(parent);
            }
        }
    }

public:
    Heap(bool isMax) : isMaxHeap(isMax) {}

    void push(int value) {
        heap.push_back(value);
        int lastIndex = heap.size() - 1;
        heapifyUp(lastIndex);
    }

    int pop() {
        if (heap.empty()) {
            return -1;
        }

        int root = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);

        return root;
    }
};


