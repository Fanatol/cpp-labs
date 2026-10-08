#include <windows.h>

#include <iostream>
#include <stdexcept>

template <typename T>
class Vector {
   private:
    T* data;  // указатель на блок памяти в куче
    int sz;   // размер – сколько элементов лежит
    int cap;  // ёмкость – сколько помещается

   public:
    // Конструктор по умолчанию – пустой вектор
    Vector() : data(nullptr), sz(0), cap(0) {}

    // Конструктор размера – вектор из n элементов, заполненных T()
    explicit Vector(int n) : data(new T[n]()), sz(n), cap(n) {}

    // Деструктор – освобождает блок памяти
    ~Vector() {
        delete[] data;
        data = nullptr;
        sz = 0;
        cap = 0;
    }

    // Доступ по индексу (неконстантный) – можно менять элемент
    T& operator[](int index) {
        if (index < 0 || index >= sz) throw std::out_of_range("Некорректный индекс!");
        return data[index];
    }

    // Доступ по индексу (константный) – только чтение
    const T& operator[](int index) const {
        if (index < 0 || index >= sz) throw std::out_of_range("Некорректный индекс!");
        return data[index];
    }

    // Количество элементов
    int size() const { return sz; }

    // Ёмкость блока
    int capacity() const { return cap; }

    // Проверка на пустоту
    bool empty() const { return sz == 0; }

    // Резервирование памяти под newCap элементов
    void reserve(int newCap) {
        if (newCap <= cap) return;
        T* newData = new T[newCap];
        for (int i = 0; i < sz; ++i) newData[i] = data[i];
        delete[] data;
        data = newData;
        cap = newCap;
    }

    // Добавление элемента в конец
    void push_back(const T& value) {
        if (sz >= cap) {
            int newCap = (cap == 0) ? 1 : cap * 2;
            reserve(newCap);
        }
        data[sz] = value;
        sz++;
    }

    // Удаление последнего элемента
    void pop_back() {
        if (sz == 0) throw std::underflow_error("Удаление из пустого контейнера");
        sz--;
    }

    // Очистка – логический размер в ноль, память не освобождается
    void clear() { sz = 0; }

    // Обмен содержимым с другим вектором
    void swap(Vector& other) {
        T* tempData = data;
        data = other.data;
        other.data = tempData;

        int tempSz = sz;
        sz = other.sz;
        other.sz = tempSz;

        int tempCap = cap;
        cap = other.cap;
        other.cap = tempCap;
    }

    // Конструктор копирования – глубокая копия (свой блок, копия элементов)
    Vector(const Vector& other) : data(new T[other.cap]), sz(other.sz), cap(other.cap) {
        for (int i = 0; i < sz; ++i) {
            data[i] = other.data[i];
        }
    }

    // Присваивание копированием – через copy-and-swap
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            Vector temp(other);
            swap(temp);
        }
        return *this;
    }

    // Конструктор перемещения – забирает ресурсы у временного
    Vector(Vector&& other) noexcept : data(other.data), sz(other.sz), cap(other.cap) {
        other.data = nullptr;
        other.sz = 0;
        other.cap = 0;
    }

    // Присваивание перемещением – освобождает своё, забирает чужое
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            sz = other.sz;
            cap = other.cap;
            other.data = nullptr;
            other.sz = 0;
            other.cap = 0;
        }
        return *this;
    }

    // Разворот элементов на месте
    void reverse() {
        int i = 0;
        int j = sz - 1;
        while (i < j) {
            T temp = data[i];
            data[i] = data[j];
            data[j] = temp;
            i++;
            j--;
        }
    }

    // Итераторы – указатели на начало и за конец
    T* begin() { return data; }
    T* end() { return data + sz; }
    const T* begin() const { return data; }
    const T* end() const { return data + sz; }

    // Константный итератор – только для чтения
    class ConstIterator {
       private:
        const T* ptr;  // указатель на константный элемент

       public:
        // Конструктор от указателя
        ConstIterator(const T* p) : ptr(p) {}

        // Разыменование – доступ к элементу только для чтения
        const T& operator*() const { return *ptr; }

        // Доступ к полям через ->
        const T* operator->() const { return ptr; }

        // Префиксный ++ – сдвиг вперёд, возвращает себя
        ConstIterator& operator++() {
            ++ptr;
            return *this;
        }

        // Постфиксный ++ – возвращает копию до сдвига
        ConstIterator operator++(int) {
            ConstIterator tmp = *this;
            ++ptr;
            return tmp;
        }

        // Префиксный -- – сдвиг назад
        ConstIterator& operator--() {
            --ptr;
            return *this;
        }

        // Постфиксный -- – возвращает копию до сдвига
        ConstIterator operator--(int) {
            ConstIterator tmp = *this;
            --ptr;
            return tmp;
        }

        // Сравнение итераторов
        bool operator==(const ConstIterator& other) const { return ptr == other.ptr; }
        bool operator!=(const ConstIterator& other) const { return ptr != other.ptr; }

        // Сдвиг на n позиций
        ConstIterator operator+(int n) const { return ConstIterator(ptr + n); }
        ConstIterator operator-(int n) const { return ConstIterator(ptr - n); }

        // Расстояние между итераторами
        int operator-(const ConstIterator& other) const { return ptr - other.ptr; }

        // Сравнение позиций
        bool operator<(const ConstIterator& other) const { return ptr < other.ptr; }
        bool operator>(const ConstIterator& other) const { return ptr > other.ptr; }
        bool operator<=(const ConstIterator& other) const { return ptr <= other.ptr; }
        bool operator>=(const ConstIterator& other) const { return ptr >= other.ptr; }
    };

    // Возвращают const_iterator (только чтение)
    ConstIterator cbegin() const { return ConstIterator(data); }
    ConstIterator cend() const { return ConstIterator(data + sz); }
};

// Функция для печати вектора через range-based for
template <typename T>
void printVector(const Vector<T>& v) {
    std::cout << "[";
    bool first = true;
    for (const T& x : v) {
        if (!first) std::cout << ", ";
        std::cout << x;
        first = false;
    }
    std::cout << "]";
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    std::cout << "=== 1. Конструкторы и push_back ===\n";
    Vector<int> v1;
    std::cout << "Пустой: size=" << v1.size() << ", cap=" << v1.capacity() << "\n";

    for (int i = 1; i <= 5; i++) {
        v1.push_back(i * 10);
        std::cout << "push_back(" << i * 10 << "): size=" << v1.size() << ", cap=" << v1.capacity()
                  << "\n";
    }
    std::cout << "v1 = ";
    printVector(v1);
    std::cout << "\n";

    std::cout << "\n=== 2. Конструктор размера ===\n";
    Vector<int> v2(5);
    std::cout << "Vector<int> v2(5): size=" << v2.size() << ", cap=" << v2.capacity() << "\n";
    std::cout << "v2 = ";
    printVector(v2);
    std::cout << "\n";

    std::cout << "\n=== 3. operator[] ===\n";
    std::cout << "v1[0] = " << v1[0] << ", v1[2] = " << v1[2] << "\n";
    v1[0] = 999;
    std::cout << "После v1[0] = 999: v1 = ";
    printVector(v1);
    std::cout << "\n";

    std::cout << "\n=== 4. Конструктор копирования (глубокая копия) ===\n";
    Vector<int> v3 = v1;
    v1.push_back(777);
    std::cout << "v3 (копия v1 до изменения) = ";
    printVector(v3);
    std::cout << "\n";
    std::cout << "v1 (после push_back) = ";
    printVector(v1);
    std::cout << "\n";

    std::cout << "\n=== 5. Оператор присваивания копированием ===\n";
    Vector<int> v4;
    v4 = v3;
    std::cout << "v4 = ";
    printVector(v4);
    std::cout << "\n";

    std::cout << "\n=== 6. Самоприсваивание ===\n";
    v4 = v4;
    std::cout << "v4 после v4 = v4: ";
    printVector(v4);
    std::cout << "\n";

    std::cout << "\n=== 7. Перемещение ===\n";
    Vector<int> v5 = std::move(v3);
    std::cout << "v5 (перемещённый из v3) = ";
    printVector(v5);
    std::cout << "\n";
    std::cout << "v3 после перемещения: size=" << v3.size() << ", cap=" << v3.capacity() << "\n";

    std::cout << "\n=== 8. reverse ===\n";
    std::cout << "До: ";
    printVector(v5);
    std::cout << "\n";
    v5.reverse();
    std::cout << "После: ";
    printVector(v5);
    std::cout << "\n";

    std::cout << "\n=== 9. pop_back и clear ===\n";
    v5.pop_back();
    std::cout << "После pop_back: ";
    printVector(v5);
    std::cout << ", size=" << v5.size() << "\n";
    v5.clear();
    std::cout << "После clear: size=" << v5.size() << ", cap=" << v5.capacity()
              << ", empty=" << (v5.empty() ? "да" : "нет") << "\n";

    std::cout << "\n=== 10. Итераторы (range-based for) ===\n";
    std::cout << "v1 через for: ";
    for (int x : v1) std::cout << x << " ";
    std::cout << "\n";

    std::cout << "\n=== 11. ConstIterator (cbegin/cend) ===\n";
    std::cout << "v1 через cbegin/cend: ";
    for (auto it = v1.cbegin(); it != v1.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    std::cout << "\n=== 12. Итераторы с явной арифметикой ===\n";
    auto it = v1.cbegin();
    std::cout << "*it = " << *it << "\n";
    it = it + 2;
    std::cout << "*(it + 2) = " << *it << "\n";
    std::cout << "Расстояние от cbegin до it: " << (it - v1.cbegin()) << "\n";

    std::cout << "\n=== 13. Исключение при выходе за границы ===\n";
    try {
        std::cout << v1[100] << "\n";
    } catch (const std::out_of_range& e) {
        std::cout << "Поймано исключение: " << e.what() << "\n";
    }

    try {
        Vector<int> empty;
        empty.pop_back();
    } catch (const std::underflow_error& e) {
        std::cout << "Поймано исключение: " << e.what() << "\n";
    }

    std::cout << "\n=== 14. Шаблон со строками ===\n";
    Vector<std::string> words;
    words.push_back("мир");
    words.push_back("труд");
    words.push_back("май");
    words.reverse();
    std::cout << "words = ";
    printVector(words);
    std::cout << "\n";

    std::cout << "\nНажмите Enter для выхода...";
    std::cin.ignore();
    std::cin.get();
    return 0;
}