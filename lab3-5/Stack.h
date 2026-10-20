#pragma once
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <string>

template <typename T>
class Stack {
   private:
    T* data;
    int topIndex;
    int capacity;
    void resize() {
        int newCapacity = capacity * 2;
        T* newData = new T[newCapacity];
        for (int i = 0; i <= topIndex; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

   public:
    Stack(int iCap = 10) : data(new T[iCap]), topIndex(-1), capacity(iCap) {}
    ~Stack() {
        delete[] data;
        data = nullptr;
        capacity = 0;
        topIndex = -1;
    }
    void push(const T& value) {
        if (topIndex == capacity - 1) resize();
        topIndex++;
        data[topIndex] = value;
    }
    T pop() {
        if (isEmpty()) throw std::underflow_error("Стек пуст!");
        T value = data[topIndex];
        topIndex--;
        return value;
    }
    T top() const {
        if (isEmpty()) throw std::underflow_error("Стек пуст!");
        return data[topIndex];
    }
    bool isEmpty() const { return topIndex == -1; }
    int size() const { return topIndex + 1; }
};

int evaluateRPN(const std::string& expr) {
    Stack<int> stack;
    std::stringstream ss(expr);
    std::string token;
    while (ss >> token) {
        if (token == "+") {
            if (stack.size() < 2) throw std::invalid_argument("Недостаточно операндов");
            int a = stack.pop();
            int b = stack.pop();
            stack.push(b + a);
        } else if (token == "-") {
            if (stack.size() < 2) throw std::invalid_argument("Недостаточно операндов");
            int a = stack.pop();
            int b = stack.pop();
            stack.push(b - a);
        } else if (token == "*") {
            if (stack.size() < 2) throw std::invalid_argument("Недостаточно операндов");
            int a = stack.pop();
            int b = stack.pop();
            stack.push(b * a);
        } else if (token == "/") {
            if (stack.size() < 2) throw std::invalid_argument("Недостаточно операндов");
            int a = stack.pop();
            int b = stack.pop();
            if (a == 0) throw std::runtime_error("Деление на 0!");
            stack.push(b / a);
        } else {
            int value = std::stoi(token);
            stack.push(value);
        }
    }

    if (stack.size() == 1) {
        return stack.pop();
    } else {
        throw std::invalid_argument("Некорректные входные данные!");
    }
}