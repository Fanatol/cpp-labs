#pragma once
#include <iostream>
#include <stdexcept>
template <typename T>
class PriorityQueue {
   private:
    T* heap;
    int count;
    int capacity;
    void resize() {
        int newCapacity = capacity * 2;
        T* newData = new T[newCapacity];
        for (int i = 0; i < count; i++) {
            newData[i] = heap[i];
        }
        delete[] heap;
        heap = newData;
        capacity = newCapacity;
    }
    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index] > heap[parent]) {
                T temp = heap[parent];
                heap[parent] = heap[index];
                heap[index] = temp;
                index = parent;
            } else {
                break;
            }
        }
    }
    void heapifyDown(int index) {
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;
            if (left < count && heap[left] > heap[largest]) {
                largest = left;
            }
            if (right < count && heap[right] > heap[largest]) {
                largest = right;
            }

            if (largest != index) {
                T temp = heap[largest];
                heap[largest] = heap[index];
                heap[index] = temp;
                index = largest;
            } else {
                break;
            }
        }
    }

   public:
    PriorityQueue(int iCap = 10) : heap(new T[iCap]), count(0), capacity(iCap) {}
    ~PriorityQueue() {
        delete[] heap;
        heap = nullptr;
        count = 0;
        capacity = 0;
    }
    void push(const T& value) {
        if (count == capacity) resize();
        heap[count] = value;
        int index = count;
        count++;
        heapifyUp(index);
    }
    T pop() {
        if (isEmpty()) throw std::underflow_error("Приоритетная очередь пуста!");
        T maxValue = heap[0];
        heap[0] = heap[count - 1];
        count--;
        heapifyDown(0);
        return maxValue;
    }
    T top() const {
        if (isEmpty()) throw std::underflow_error("Приоритетная очередь пуста!");
        return heap[0];
    }
    bool isEmpty() const { return count == 0; }
    int size() const { return count; }
};

void findKSmallest(const int* arr, int n, int k) {
    PriorityQueue<int> pq;
    for (int i = 0; i < n; i++) {
        pq.push(arr[i]);
        if (pq.size() > k) pq.pop();
    }
    while (!pq.isEmpty()) {
        std::cout << pq.pop() << " ";
    }
}