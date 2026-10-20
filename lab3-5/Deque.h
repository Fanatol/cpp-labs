#pragma once
#include <stdexcept>

template <typename T>
class Deque {
   private:
    T* data;
    int frontIndex;
    int rearIndex;
    int count;
    int capacity;
    void resize() {
        int newCapacity = capacity * 2;
        T* newData = new T[newCapacity];
        for (int i = 0; i < count; i++) {
            newData[i] = data[(frontIndex + i) % capacity];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
        frontIndex = 0;
        rearIndex = count;
    }

   public:
    Deque(int iCap = 10)
        : data(new T[iCap]), frontIndex(0), rearIndex(0), count(0), capacity(iCap) {}
    ~Deque() {
        delete[] data;
        data = nullptr;
        frontIndex = 0;
        rearIndex = 0;
        count = 0;
        capacity = 0;
    }
    void push_front(const T& value) {
        if (count == capacity) resize();
        frontIndex = (frontIndex - 1 + capacity) % capacity;
        data[frontIndex] = value;
        count++;
    }
    void push_back(const T& value) {
        if (count == capacity) resize();
        data[rearIndex] = value;
        rearIndex = (rearIndex + 1) % capacity;
        count++;
    }
    T pop_front() {
        if (isEmpty()) throw std::underflow_error("Дек пуст!");
        T value = data[frontIndex];
        frontIndex = (frontIndex + 1) % capacity;
        count--;
        return value;
    }
    T pop_back() {
        if (isEmpty()) throw std::underflow_error("Дек пуст!");
        rearIndex = (rearIndex - 1 + capacity) % capacity;
        T value = data[rearIndex];
        count--;
        return value;
    }
    T front() const {
        if (isEmpty()) throw std::underflow_error("Дек пуст!");
        return data[frontIndex];
    }
    T back() const {
        if (isEmpty()) throw std::underflow_error("Дек пуст!");
        return data[(rearIndex - 1 + capacity) % capacity];
    }
    bool isEmpty() const { return count == 0; }
    int size() const { return count; }
};
