#include <iostream> 
#include <cmath> 
#include <limits> 

// класс Point для точки с координатами x и y
class Point {
private:
    double x; 
    double y; 

public:
    // Конструктор по умолчанию с инициализацией координат (0, 0)
    Point() : x(0), y(0) {}

    // Конструктор для инициализации начальных значений координат
    Point(double xValue, double yValue) : x(xValue), y(yValue) {}

    // Конструктор копирования, создающий копию существующего объекта Point
    Point(const Point &p) : x(p.x), y(p.y) {}

    // Метод для вычисления расстояния от точки до начала координат
    double DistanceToOrigin() const {
        return std::sqrt(x * x + y * y); // Вычисляем и возвращаем расстояние
    }

    // Перегрузка оператора вывода для удобного отображения объекта Point
    friend std::ostream &operator<<(std::ostream &os, const Point &p) {
        os << "Point(" << p.x << ", " << p.y << ")"; // Формируем строку для вывода
        return os; 
    }

    // Унарные операции
    Point& operator--() { // Оператор префиксного декремента, уменьшающий координаты на 1
        --x; 
        --y; 
        return *this; // Возвращаем текущий объект
    }

    void SwapCoordinates() { // Метод для замены координат x и y местами
        std::swap(x, y); 
    }

    // Операции приведения типа
    operator int() const { // Неявное приведение координаты x к целому типу
        return static_cast<int>(x); // Приводим x к типу int
    }

    explicit operator double() const { // Явное приведение координаты y к типу double
        return y; 
    }

    // Бинарные операции
    Point operator-(int value) const { // Оператор вычитания: уменьшение x на целое число
        return Point(x - value, y); // Возвращаем новую точку с уменьшенным x
    }

    double DistanceToPoint(const Point &p) const { // Метод для вычисления расстояния до другой точки
        return std::sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y)); // Вычисляем и возвращаем расстояние
    }
};

// Функция для обработки ошибок
double getValidInput(const std::string &coordinateName) {
    double value; // Переменная для хранения введенного значения
    while (true) { 
        std::cout << "Введите " << coordinateName << ": "; 
        std::cin >> value; // Считываем значение

        // Проверяем успешность ввода
        if (std::cin.fail()) {
            std::cin.clear(); // Сбрасываем состояние потока ввода
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорируем остаток ввода
            std::cout << "Некорректный ввод. Повторите попытку." << std::endl; 
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорируем остаток ввода
            return value; // Возвращаем корректное введенное значение
        }
    }
}

int main() {
    int choice; 
    std::cout << "Выберите задание (1 или 2): "; 
    std::cin >> choice; // Считываем выбор

    // Проверяем, произошла ли ошибка ввода или не был выбран корректный номер задания
    if (std::cin.fail() || (choice != 1 && choice != 2)) {
        std::cout << "Некорректный выбор задания." << std::endl; 
        return 1; 
    }

    if (choice == 1) { 
        double x = getValidInput("координату x"); 
        double y = getValidInput("координату y"); 
        Point p(x, y); // Создаем объект Point с введенными координатами

        std::cout << "Создана " << p << std::endl; 
        std::cout << "Расстояние до начала координат: " << p.DistanceToOrigin() << std::endl; // Выводим расстояние до начала координат
    } else if (choice == 2) {
        double x = getValidInput("координату x"); 
        double y = getValidInput("координату y"); 
        Point p(x, y); 

        std::cout << "Создана " << p << std::endl; 

        int operation; 
        std::cout << "Выберите операцию:\n"; 
        std::cout << "1: уменьшить x и y на 1\n"; 
        std::cout << "2: поменять координаты местами\n"; 
        std::cout << "3: целая часть координаты x\n"; 
        std::cout << "4: координата y\n"; 
        std::cout << "5: уменьшить x на целое число\n"; 
        std::cout << "6: расстояние до другой точки\n"; 
        std::cout << "Введите номер операции:\n"; 
        std::cin >> operation; // Считываем номер операции

        // Проверяем ввод операции на корректность
        if (std::cin.fail() || (operation < 1 || operation > 6)) {
            std::cin.clear(); // Сбрасываем состояние потока
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорируем остаток ввода
            std::cout << "Некорректный ввод операции." << std::endl;
            return 1; 
        }

        switch (operation) { // Выполняем выбранную операцию
            case 1: // Уменьшение x и y на 1
                --p; // 
                std::cout << "Координаты после уменьшения: " << p << std::endl; 
                break;
            case 2: // Поменять координаты местами
                p.SwapCoordinates(); // Вызываем метод для смены координат
                std::cout << "Координаты после перестановки: " << p << std::endl; 
                break;
            case 3: // Получить целую часть координаты x
                std::cout << "Целая часть координаты x: " << static_cast<int>(p) << std::endl; // Приводим x к типу int и выводим
                break;
            case 4: // Получить координату y
                std::cout << "Координата y: " << static_cast<double>(p) << std::endl; // Приводим y к типу double и выводим
                break;
            case 5: { // Уменьшить x на целое число
                int value; // Переменная для хранения введенного числа
                std::cout << "Введите значение для уменьшения x: ";
                std::cin >> value; // Считываем число
                if (!std::cin.fail()) { // Проверяем, успешен ли ввод
                    p = p - value; // Вызываем оператор вычитания
                    std::cout << "Координаты после уменьшения x: " << p << std::endl; 
                } else {
                    std::cout << "Некорректный ввод. Необходимо ввести целое число." << std::endl; 
                }
                break;
            }
            case 6: { // Рассчитать расстояние до другой точки
                double x2 = getValidInput("координату x другой точки"); 
                double y2 = getValidInput("координату y другой точки"); 
                Point p2(x2, y2); // Создаем другую точку
                std::cout << "Расстояние до точки " << p2 << ": " << p.DistanceToPoint(p2) << std::endl; // Выводим расстояние до другой точки
                break;
            }
            default: // Обработка некорректного ввода операции
                std::cout << "Некорректный выбор операции." << std::endl; 
        } 
    } 

    return 0; 
}
