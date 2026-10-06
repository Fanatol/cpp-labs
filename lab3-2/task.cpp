#include <windows.h>

#include <chrono>
#include <iostream>
#include <list>

template <typename Func>
long long measureTime(Func func) {
    auto startTime = std::chrono::high_resolution_clock::now();
    func();
    auto endTime = std::chrono::high_resolution_clock::now();
    auto workTime = endTime - startTime;
    return std::chrono::duration_cast<std::chrono::microseconds>(workTime).count();
}

template <typename T>
struct Node {
    T value;
    Node* prev;
    Node* next;
    Node(const T& v) : value(v), prev(nullptr), next(nullptr) {}
};

template <typename T>
class List {
   private:
    Node<T>* head;
    Node<T>* tail;
    int count;

   public:
    List() : head(nullptr), tail(nullptr), count(0) {}
    ~List() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
        count = 0;
    }
    void push_front(const T& value) {
        Node<T>* newNode = new Node<T>(value);
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
        Node<T>* newNode = new Node<T>(value);
        if (tail == nullptr) {
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
        if (head == nullptr) return;
        Node<T>* temp = head;
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
        if (tail == nullptr) return;
        Node<T>* temp = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        count--;
    }

    void insert(int index, const T& value) {
        if (index < 0 or index > count) return;
        if (index == 0) {
            push_front(value);
            return;
        }
        if (index == count) {
            push_back(value);
            return;
        }

        Node<T>* newNode = new Node<T>(value);
        Node<T>* current = head;
        int total = 0;
        while (total != index) {
            current = current->next;
            total++;
        }
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
        count++;
    }

    void erase(int index) {
        if (index < 0 or index > count - 1) return;
        if (index == 0) {
            pop_front();
            return;
        }
        if (index == count - 1) {
            pop_back();
            return;
        }

        Node<T>* current = head;
        int total = 0;
        while (total != index) {
            current = current->next;
            total++;
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        count--;
    }

    int size() const { return count; }

    void print() const {
        Node<T>* temp = head;
        std::cout << "Элементы списка: ";
        while (temp != nullptr) {
            std::cout << temp->value;
            if (temp->next != nullptr) std::cout << ", ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    std::cout << "=== Демонстрация работы List ===\n";

    List<int> demo;
    std::cout << "\n--- Пустой список ---\n";
    demo.print();
    std::cout << "Размер: " << demo.size() << "\n";

    std::cout << "\n--- push_back(1, 2, 3) ---\n";
    demo.push_back(1);
    demo.push_back(2);
    demo.push_back(3);
    demo.print();
    std::cout << "Размер: " << demo.size() << "\n";

    std::cout << "\n--- push_front(0) ---\n";
    demo.push_front(0);
    demo.print();
    std::cout << "Размер: " << demo.size() << "\n";

    std::cout << "\n--- insert(2, 99) ---\n";
    demo.insert(2, 99);
    demo.print();
    std::cout << "Размер: " << demo.size() << "\n";

    std::cout << "\n--- erase(2) ---\n";
    demo.erase(2);
    demo.print();
    std::cout << "Размер: " << demo.size() << "\n";

    std::cout << "\n--- pop_front() ---\n";
    demo.pop_front();
    demo.print();
    std::cout << "Размер: " << demo.size() << "\n";

    std::cout << "\n--- pop_back() ---\n";
    demo.pop_back();
    demo.print();
    std::cout << "Размер: " << demo.size() << "\n";

    std::cout << "\n--- Проверка границ ---\n";
    demo.erase(-1);
    demo.erase(100);
    demo.insert(-1, 5);
    demo.insert(100, 5);
    demo.print();
    std::cout << "Размер: " << demo.size() << " (не изменился)\n";

    std::cout << "\n--- Шаблон со строками ---\n";
    List<std::string> words;
    words.push_back("мир");
    words.push_back("труд");
    words.push_front("Привет");
    words.insert(2, "и");
    words.print();
    std::cout << "Размер: " << words.size() << "\n";

    std::cout << "\n\n=== Замеры производительности ===\n";

    int sizes[] = {1000, 5000, 10000, 50000, 100000};

    std::cout << "\n=== push_back ===\n";
    for (int n : sizes) {
        List<int> myList;
        std::list<int> stdList;
        long long tMy = measureTime([&]() {
            for (int i = 0; i < n; i++) myList.push_back(i);
        });
        long long tStd = measureTime([&]() {
            for (int i = 0; i < n; i++) stdList.push_back(i);
        });
        std::cout << "N=" << n << ": мой=" << tMy << " мкс, std=" << tStd << " мкс\n";
    }

    std::cout << "\n=== push_front ===\n";
    for (int n : sizes) {
        List<int> myList;
        std::list<int> stdList;
        long long tMy = measureTime([&]() {
            for (int i = 0; i < n; i++) myList.push_front(i);
        });
        long long tStd = measureTime([&]() {
            for (int i = 0; i < n; i++) stdList.push_front(i);
        });
        std::cout << "N=" << n << ": мой=" << tMy << " мкс, std=" << tStd << " мкс\n";
    }

    std::cout << "\n=== pop_back (после заполнения) ===\n";
    for (int n : sizes) {
        List<int> myList;
        std::list<int> stdList;
        for (int i = 0; i < n; i++) {
            myList.push_back(i);
            stdList.push_back(i);
        }
        long long tMy = measureTime([&]() {
            while (myList.size() > 0) myList.pop_back();
        });
        long long tStd = measureTime([&]() {
            while (!stdList.empty()) stdList.pop_back();
        });
        std::cout << "N=" << n << ": мой=" << tMy << " мкс, std=" << tStd << " мкс\n";
    }

    std::cout << "\n=== pop_front (после заполнения) ===\n";
    for (int n : sizes) {
        List<int> myList;
        std::list<int> stdList;
        for (int i = 0; i < n; i++) {
            myList.push_back(i);
            stdList.push_back(i);
        }
        long long tMy = measureTime([&]() {
            while (myList.size() > 0) myList.pop_front();
        });
        long long tStd = measureTime([&]() {
            while (!stdList.empty()) stdList.pop_front();
        });
        std::cout << "N=" << n << ": мой=" << tMy << " мкс, std=" << tStd << " мкс\n";
    }

    std::cout << "\n=== insert в середину (N/2 раз) ===\n";
    int sizesInsert[] = {1000, 5000, 10000};
    for (int n : sizesInsert) {
        List<int> myList;
        std::list<int> stdList;
        for (int i = 0; i < n; i++) {
            myList.push_back(i);
            stdList.push_back(i);
        }
        int half = n / 2;
        long long tMy = measureTime([&]() {
            for (int i = 0; i < half; i++) myList.insert(n / 2, i);
        });
        long long tStd = measureTime([&]() {
            for (int i = 0; i < half; i++) {
                auto it = stdList.begin();
                for (int j = 0; j < n / 2; j++) ++it;
                stdList.insert(it, i);
            }
        });
        std::cout << "N=" << n << ": мой=" << tMy << " мкс, std=" << tStd << " мкс\n";
    }

    std::cout << "\nНажмите Enter для выхода...";
    std::cin.ignore();
    std::cin.get();
    return 0;
}