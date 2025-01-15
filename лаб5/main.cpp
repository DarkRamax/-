#include <iostream>
#include "Vect.h"

int main() {
    try {
        Vect<int> vect = {-10, 15, -5, 20, 0, -1, 5};

        std::cout << "Positive elements: ";
        auto pos_iter = vect.positive_iterator();
        while (pos_iter.has_next()) {
            std::cout << pos_iter.next() << " ";
        }
        std::cout << "\n";

        std::cout << "Negative elements: ";
        auto neg_iter = vect.negative_iterator();
        while (neg_iter.has_next()) {
            std::cout << neg_iter.next() << " ";
        }
        std::cout << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
