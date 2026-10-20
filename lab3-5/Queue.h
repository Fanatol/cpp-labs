#pragma once
#include <stdexcept>

#include "Stack.h"

template <typename T>
class Queue {
   private:
    Stack<T> input;   // кладём
    Stack<T> output;  // берём
    void moveInputToOutput() {
        while (!input.isEmpty()) {
            T value = input.pop();
            output.push(value);
        }
    }

   public:
    Queue() = default;
    ~Queue() = default;
    void enqueue(const T& value) { input.push(value); }
    T dequeue() {
        if (isEmpty()) throw std::underflow_error("Очередь пуста!");
        if (output.isEmpty()) moveInputToOutput();
        return output.pop();
    }
    T front() {
        if (isEmpty()) throw std::underflow_error("Очередь пуста!");
        if (output.isEmpty()) moveInputToOutput();
        return output.top();
    }
    bool isEmpty() const { return input.isEmpty() && output.isEmpty(); }
    int size() const { return input.size() + output.size(); }
};
