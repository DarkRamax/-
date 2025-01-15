#include <iostream>
#include <vector>
#include <algorithm>

// Шаблонный класс MSet
template <typename T>
class MSet {
private:
    std::vector<T> elements; // Хранилище элементов множества

public:
    // Конструктор по умолчанию
    MSet() = default;

    // Метод для добавления элемента в множество
    void add(const T& value) {
        elements.push_back(value);
        std::sort(elements.begin(), elements.end()); // Сортировка после добавления
    }

    // Метод для удаления всех вхождений элемента из множества
    void remove(const T& value) {
        elements.erase(std::remove(elements.begin(), elements.end(), value), elements.end());
    }

    // Метод для проверки, содержится ли элемент в множестве
    bool contains(const T& value) const {
        return std::binary_search(elements.begin(), elements.end(), value);
    }

    // Метод для получения количества элементов в множестве
    size_t size() const {
        return elements.size();
    }

    // Метод для отображения элементов множества
    void display() const {
        for (const auto& elem : elements) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const MSet& mset) {
        for (const auto& elem : mset.elements) {
            os << elem << " ";
        }
        return os;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    MSet<int> intSet;

    intSet.add(5);
    intSet.add(3);
    intSet.add(7);
    intSet.add(5); // Повторяющийся элемент

    std::cout << "Множество после добавления элементов: ";
    intSet.display();

    intSet.remove(5);
    std::cout << "Множество после удаления элемента 5: ";
    intSet.display();

    std::cout << "Содержит ли множество элемент 3? " << (intSet.contains(3) ? "Да" : "Нет") << std::endl;

    std::cout << "Размер множества: " << intSet.size() << std::endl;

    return 0;
}
