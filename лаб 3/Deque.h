#ifndef DEQUE_H
#define DEQUE_H

#include "Vect.h"

template <typename T>
class Deque {
private:
    Vect<T> data;

public:
    Deque() = default;

    void push_front(const T& value) {
        data.push_back(T());
        for (size_t i = data.size() - 1; i > 0; --i) {
            data[i] = data[i - 1];
        }
        data[0] = value;
    }

    void push_back(const T& value) {
        data.push_back(value);
    }

    void pop_front() {
        if (data.size() == 0) {
            throw VectPopError();
        }
        for (size_t i = 1; i < data.size(); ++i) {
            data[i - 1] = data[i];
        }
        data.pop_back();
    }

    void pop_back() {
        data.pop_back();
    }

    T& front() {
        if (data.size() == 0) {
            throw VectPopError();
        }
        return data[0];
    }

    T& back() {
        if (data.size() == 0) {
            throw VectPopError();
        }
        return data[data.size() - 1];
    }

    size_t size() const {
        return data.size();
    }
};

#endif
