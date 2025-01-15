#include <iostream>
#include "Deque.h"

int main() {
    try {
        Deque<int> deque;
        deque.push_back(10);
        deque.push_front(20);
        deque.push_back(30);

        std::cout << "Front: " << deque.front() << "\n";
        std::cout << "Back: " << deque.back() << "\n";
        std::cout << "Size: " << deque.size() << "\n";

        deque.pop_front();
        std::cout << "After pop_front, front: " << deque.front() << "\n";

        deque.pop_back();
        std::cout << "After pop_back, back: " << deque.back() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
