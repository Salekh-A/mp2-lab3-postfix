#ifndef __TSTACK_H__
#define __TSTACK_H__

#include <stdexcept>
using namespace std;

template <typename T>
class TStack {
private:
    T* data;
    int capacity;
    int topIdx;

public:
    TStack(int size = 100) {
        if (size <= 0) throw invalid_argument("Stack size must be positive");
        capacity = size;
        topIdx = -1;
        data = new T[capacity];
    }

    ~TStack() {
        delete[] data;
    }

    void push(const T& value) {
        if (isFull()) throw runtime_error("Stack overflow");
        data[++topIdx] = value;
    }

    T pop() {
        if (isEmpty()) throw runtime_error("Stack underflow");
        return data[topIdx--];
    }

    T& top() {
        if (isEmpty()) throw runtime_error("Stack is empty");
        return data[topIdx];
    }

    const T& top() const {
        if (isEmpty()) throw runtime_error("Stack is empty");
        return data[topIdx];
    }

    bool isEmpty() const {
        return topIdx == -1;
    }

    bool isFull() const {
        return topIdx == capacity - 1;
    }

    int size() const {
        return topIdx + 1;
    }
};

#endif