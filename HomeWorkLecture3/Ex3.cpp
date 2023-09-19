#include <iostream>
using namespace std;

// Doubly linked list node structure
struct Node {
    int data;
    Node* prev;
    Node* next;

    Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};

// Doubly linked list class
class DoublyLinkedList {
public:
    Node* head;
    Node* tail;

    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void insert(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    int count_triplets() {
        int count = 0;
        Node* current = head;

        while (current != nullptr && current->next != nullptr && current->next->next != nullptr) {
            int sum = current->data + current->next->data + current->next->next->data;
            if (sum == 0) {
                count++;
            }
            current = current->next;
        }

        return count;
    }
};

int main() {
    int n;
    cin >> n;

    DoublyLinkedList linkedList;

    for (int i = 0; i < n; i++) {
        int value;
        cin >> value;
        linkedList.insert(value);
    }

    int result = linkedList.count_triplets();

    cout << result << endl;

    return 0;
}
