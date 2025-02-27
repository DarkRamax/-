#ifndef VECT_H
#define VECT_H

#include <iostream>
#include <stdexcept>
#include <initializer_list>

// Exception classes
class CustomException : public std::exception {
public:
    explicit CustomException(const char* message) : msg(message) {}
    const char* what() const noexcept override { return msg; }
private:
    const char* msg;
};

class VectRangeError : public CustomException {
public:
    VectRangeError() : CustomException("Index out of range") {}
};

class VectPopError : public CustomException {
public:
    VectPopError() : CustomException("Pop from empty vector") {}
};

// Template class Vect
template <typename T>
class Vect {
private:
    T* data;
    size_t capacity;
    size_t length;

    void allocate(size_t new_capacity) {
        T* new_data = new T[new_capacity]();
        for (size_t i = 0; i < length; ++i) {
            new_data[i] = std::move(data[i]);
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    Vect() : data(nullptr), capacity(0), length(0) {}

    Vect(size_t size) : data(new T[size]()), capacity(size), length(size) {}

    Vect(std::initializer_list<T> list) : Vect(list.size()) {
        size_t i = 0;
        for (const T& item : list) {
            data[i++] = item;
        }
    }

    ~Vect() {
        delete[] data;
    }

    Vect(const Vect& other) : data(new T[other.capacity]()), capacity(other.capacity), length(other.length) {
        for (size_t i = 0; i < length; ++i) {
            data[i] = other.data[i];
        }
    }

    Vect& operator=(const Vect& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            length = other.length;
            data = new T[capacity]();
            for (size_t i = 0; i < length; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    T& operator[](size_t index) {
        if (index >= length) {
            throw VectRangeError();
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= length) {
            throw VectRangeError();
        }
        return data[index];
    }

    void push_back(const T& value) {
        if (length == capacity) {
            allocate(capacity == 0 ? 1 : capacity * 2);
        }
        data[length++] = value;
    }

    void pop_back() {
        if (length == 0) {
            throw VectPopError();
        }
        --length;
    }

    size_t size() const {
        return length;
    }

    size_t get_capacity() const {
        return capacity;
    }

    void clear() {
        delete[] data;
        data = nullptr;
        capacity = length = 0;
    }

    // Iterators
    class Iterator {
    public:
        virtual bool has_next() const = 0;
        virtual T& next() = 0;
        virtual ~Iterator() = default;
    };

    class PositiveIterator : public Iterator {
    private:
        Vect& vect;
        size_t index;
    public:
        PositiveIterator(Vect& v) : vect(v), index(0) {
            while (index < vect.size() && vect[index] <= 0) {
                ++index;
            }
        }

        bool has_next() const override {
            return index < vect.size();
        }

        T& next() override {
            if (!has_next()) {
                throw CustomException("No more positive elements");
            }
            T& value = vect[index++];
            while (index < vect.size() && vect[index] <= 0) {
                ++index;
            }
            return value;
        }
    };

    class NegativeIterator : public Iterator {
    private:
        Vect& vect;
        size_t index;
    public:
        NegativeIterator(Vect& v) : vect(v), index(0) {
            while (index < vect.size() && vect[index] >= 0) {
                ++index;
            }
        }

        bool has_next() const override {
            return index < vect.size();
        }

        T& next() override {
            if (!has_next()) {
                throw CustomException("No more negative elements");
            }
            T& value = vect[index++];
            while (index < vect.size() && vect[index] >= 0) {
                ++index;
            }
            return value;
        }
    };

    PositiveIterator positive_iterator() {
        return PositiveIterator(*this);
    }

    NegativeIterator negative_iterator() {
        return NegativeIterator(*this);
    }
};

#endif
