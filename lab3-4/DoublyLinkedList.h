#include <iostream>
#include <stdexcept>

template <typename T>
class DoublyLinkedList {
   private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& v) : data(v), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int count;

   public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}
    ~DoublyLinkedList() { clear(); }
    void push_front(const T& value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        count++;
    }

    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    void pop_front() {
        if (head == nullptr) throw std::underflow_error("List is empty");
        Node* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        count--;
    }

    void pop_back() {
        if (tail == nullptr) throw std::underflow_error("List is empty");
        Node* temp = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        count--;
    }

    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current->next;
            delete current;
            current = temp;
        }
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    int size() const { return count; }

    bool empty() const { return count == 0; }

    Node* find(const T& value) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) return current;
            current = current->next;
        }
        return nullptr;
    }

    void insert_after(Node* node, const T& value) {
        if (node == nullptr) {
            push_front(value);
            return;
        }
        Node* newNode = new Node(value);
        newNode->next = node->next;
        newNode->prev = node;
        if (node->next != nullptr)
            node->next->prev = newNode;
        else
            tail = newNode;

        node->next = newNode;
        count++;
    }

    void erase(Node* node) {
        if (node == nullptr) return;
        if (node == head) {
            pop_front();
            return;
        }
        if (node == tail) {
            pop_back();
            return;
        }
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
        count--;
    }

    void reverse() {
        if (head == nullptr or count == 1) return;
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current->next;
            current->next = current->prev;
            current->prev = temp;
            current = temp;
        }
        Node* temp = head;
        head = tail;
        tail = temp;
    }

    void merge(DoublyLinkedList& other) {
        if (other.head == nullptr) return;
        if (head == nullptr) {
            head = other.head;
            tail = other.tail;
            count = other.count;
            other.head = nullptr;
            other.tail = nullptr;
            other.count = 0;
            return;
        }
        Node* a = head;
        Node* b = other.head;
        Node dummy(T{});
        Node* last = &dummy;
        while (a != nullptr and b != nullptr) {
            if (a->data <= b->data) {
                last->next = a;
                a->prev = last;
                a = a->next;
            } else {
                last->next = b;
                b->prev = last;
                b = b->next;
            }
            last = last->next;
        }

        while (a != nullptr) {
            last->next = a;
            a->prev = last;
            a = a->next;
            last = last->next;
        }
        while (b != nullptr) {
            last->next = b;
            b->prev = last;
            b = b->next;
            last = last->next;
        }
        head = dummy.next;
        head->prev = nullptr;
        tail = last;
        count = count + other.count;
        other.head = nullptr;
        other.tail = nullptr;
        other.count = 0;
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

    void printReverse() const {
        if (head == nullptr) {
            std::cout << "[]";
            return;
        }
        std::cout << "[";
        Node* current = tail;
        while (current->prev != nullptr) {
            std::cout << current->data << ", ";
            current = current->prev;
        }
        std::cout << current->data << "]" << std::endl;
    }

    bool operator==(const DoublyLinkedList& other) const {
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

    bool operator!=(const DoublyLinkedList& other) const { return !(*this == other); }

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

        Iterator& operator--() {
            ptr = ptr->prev;
            return *this;
        }
        Iterator operator--(int) {
            Iterator temp = *this;
            ptr = ptr->prev;
            return temp;
        }

        bool operator==(const Iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
    };

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};