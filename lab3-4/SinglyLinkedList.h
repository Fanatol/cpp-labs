#include <iostream>
#include <stdexcept>

template <typename T>
class SinglyLinkedList {
   private:
    struct Node {
        T data;
        Node* next;
        Node(const T& v) : data(v), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int count;

   public:
    SinglyLinkedList() : head(nullptr), tail(nullptr), count(0) {}

    ~SinglyLinkedList() { clear(); }

    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    void push_front(const T& value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            tail = newNode;
            head = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        count++;
    }

    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            tail = newNode;
            head = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    void pop_front() {
        if (head == nullptr) throw std::underflow_error("List is empty");
        Node* temp = head;
        head = head->next;
        if (head == nullptr) tail = nullptr;
        delete temp;
        count--;
    }

    void pop_back() {
        if (head == nullptr) throw std::underflow_error("List is empty");
        if (head == tail) {
            clear();
            return;
        }

        Node* current = head;
        while (current->next != tail) {
            current = current->next;
        }
        delete tail;
        tail = current;
        tail->next = nullptr;
        count--;
    }

    Node* find(const T& value) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) return current;
            current = current->next;
        }
        return nullptr;
    }

    bool remove(const T& value) {
        if (head == nullptr) return false;
        if (head->data == value) {
            pop_front();
            return true;
        }
        if (tail->data == value) {
            pop_back();
            return true;
        }

        Node* current = head;
        while (current->next != nullptr and current->next->data != value) {
            current = current->next;
        }
        if (current->next == nullptr) return false;
        Node* toDelete = current->next;
        current->next = toDelete->next;
        delete toDelete;
        count--;
        return true;
    }

    void print() const {
        if (head == nullptr) {
            std::cout << "[]";
            return;
        }
        std::cout << "[";
        Node* current = head;
        while (current->next != nullptr) {
            std::cout << current->data << ", ";
            current = current->next;
        }
        std::cout << current->data << "]" << std::endl;
    }

    int size() const { return count; }

    bool empty() const { return count == 0; }

    bool operator==(const SinglyLinkedList& other) const {
        if (count != other.count) return false;
        Node* current = head;
        Node* otherCurrent = other.head;
        while (current != nullptr) {
            if (current->data != otherCurrent->data) return false;
            current = current->next;
            otherCurrent = otherCurrent->next;
        }
        return true;
    }

    bool operator!=(const SinglyLinkedList& other) const { return !(*this == other); }

    class Iterator {
       private:
        Node* ptr;

       public:
        Iterator(Node* p) : ptr(p) {}

        T& operator*() { return ptr->data; }

        Iterator& operator++() {
            ptr = ptr->next;
            return *this;
        }
        Iterator operator++(int) {
            Iterator temp = *this;
            ptr = ptr->next;
            return temp;
        }

        bool operator==(const Iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
    };
    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};
