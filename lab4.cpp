#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

int main() {
    setlocale(LC_ALL, "Russian");
    std::string input;
    std::cout << "Введите строку символов: "; // Запрашиваем у пользователя ввод строки
    std::getline(std::cin, input); // Считываем всю строку

    std::string lower, upper, hexNumbers; // Для хранения букв, чисел в hex формате
    std::vector<int> numbers; // Вектор для хранения найденных цифр

    for (char ch : input) { // Проходим по каждому символу строки
        if (islower(ch)) {
            lower += ch; // Если символ в нижнем регистре, добавляем в lower
        }
        else if (isupper(ch)) {
            upper += ch; // Если символ в верхнем регистре, добавляем в upper
        }
        else if (isdigit(ch)) {
            numbers.push_back(ch - '0'); // Если символ - цифра, добавляем в вектор чисел
            std::stringstream ss; // Создаем стрим для форматирования
            ss << std::hex << (ch - '0'); // Конвертируем цифру в HEX
            hexNumbers += ss.str(); // Добавляем в строку hexNumbers
        }
        else if (ch == ' ') {
            hexNumbers += '#'; // Заменяем пробел на #
        }
        else {
            hexNumbers += ch; // Добавляем остальные символы как есть
        }
    }

    // Вывод на экран собранной информации
    std::cout << "Все буквы в нижнем регистре: " << lower << std::endl;
    std::cout << "Все буквы в большом регистре: " << upper << std::endl;
    std::cout << "Все числа в HEX формате: " << hexNumbers << std::endl;

    // Проверка, есть ли найденные числа
    if (!numbers.empty()) {
        double sum = 0;
        for (int num : numbers) sum += num; // Считаем сумму всех цифр
        double average = sum / numbers.size(); // Находим среднее арифметическое

        // Открываем файл для записи
        std::ofstream outFile("output.txt");
        for (char ch : input) {
            if (isdigit(ch)) {
                outFile << average; // Заменяем цифры на среднее арифметическое
            }
            else {
                outFile << ch; // Записываем остальные символы в файл
            }
        }
        outFile.close(); // Закрываем файл
    }

    return 0; // Завершаем программу
}