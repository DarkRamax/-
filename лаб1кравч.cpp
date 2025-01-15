#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>

// Пользовательский класс исключений
class CustomException : public std::exception {
private:
    std::string message;
    double value;
    int errorCode;

public:
    CustomException(const std::string& msg, double val, int code)
        : message(msg), value(val), errorCode(code) {}

    const char* what() const noexcept override {
        return message.c_str();
    }

    double getValue() const { return value; }
    int getErrorCode() const { return errorCode; }
};

// Функция для вычисления z1
void calculateZ1(double a, double b, double& z1) {
    if (a <= 0 || b <= 0) {
        throw CustomException("Аргумент должен быть больше нуля", a <= 0 ? a : b, 101);
    }

    double numerator = (a - 1) * sqrt(a) - (b - 1) * sqrt(b);
    double denominator = sqrt(a * b) + a * a - a + b;

    if (denominator == 0) {
        throw CustomException("Деление на ноль в z1", denominator, 102);
    }

    z1 = numerator / denominator;
}

// Функция для вычисления z2
void calculateZ2(double a, double b, double& z2) {
    if (a <= 0 || b <= 0) {
        throw CustomException("Аргумент должен быть больше нуля", a <= 0 ? a : b, 101);
    }

    if (a == 0) {
        throw CustomException("Деление на ноль в z2", a, 102);
    }

    z2 = (sqrt(a) - sqrt(b)) / a;
}

int main() {
    setlocale(LC_ALL, "Russian");
    double a, b, z1, z2;

    try {
        std::cout << "Введите a и b: ";
        std::cin >> a >> b;

        calculateZ1(a, b, z1);
        calculateZ2(a, b, z2);

        std::cout << "z1 = " << z1 << std::endl;
        std::cout << "z2 = " << z2 << std::endl;

        if (fabs(z1 - z2) < 1e-6) {
            std::cout << "Значения z1 и z2 приблизительно равны." << std::endl;
        }
        else {
            std::cout << "Значения z1 и z2 отличаются." << std::endl;
        }

    }
    catch (const CustomException& e) {
        std::cerr << "Исключение: " << e.what() << std::endl;
        std::cerr << "Значение: " << e.getValue() << ", Код ошибки: " << e.getErrorCode() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Общее исключение: " << e.what() << std::endl;
    }

    return 0;
}
