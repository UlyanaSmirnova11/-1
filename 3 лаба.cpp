#include <iostream> 
#include <vector> 
#include <iomanip> 
#include <stdexcept> 
#include <limits> 
#include <regex> 

using namespace std; 

// Класс Point (Точка)
class Point {
private:
    int x, y; // Координаты точки

public:
    // Конструктор для инициализации точки
    Point(int x, int y) : x(x), y(y) {}

    // Метод для печати координат точки
    string print() const {
        return "{" + to_string(x) + ";" + to_string(y) + "}";
    }
};

// Класс Line (Линия)
class Line {
private:
    Point start; 
    Point end; 

public:
    // Конструктор для инициализации линии с заданными точками
    Line(const Point& start, const Point& end) : start(start), end(end) {}

    // Метод для печати информации о линии
    string print() const {
        return "Линия от " + start.print() + " до " + end.print();
    }

    // Метод для изменения начальной точки линии
    void setStart(const Point& newStart) {
        start = newStart; 
    }

    // Метод для изменения конечной точки линии
    void setEnd(const Point& newEnd) {
        end = newEnd; 
    }

    // Метод для получения начальной точки
    Point getStart() const { return start; }

    // Метод для получения конечной точки
    Point getEnd() const { return end; }
};

// Класс Student (Студент)
class Student {
private:
    string name; 
    vector<int> grades; 

public:
    // Конструктор для инициализации студента с именем и оценками
    Student(const string& name, const vector<int>& grades = {}) : name(name), grades(grades) {}

    // Метод для печати информации о студенте
    string print() const {
        string result = name + ": [";
        for (size_t i = 0; i < grades.size(); ++i) {
            result += to_string(grades[i]); // Добавляем оценку к строке
            if (i < grades.size() - 1) result += ", "; 
        }
        result += "]"; 
        return result;
    }

    // Метод для вычисления среднего арифметического оценок
    double average() const {
        if (grades.empty()) return 0; // Если оценки отсутствуют, возвращаем 0
        double sum = 0;
        for (int grade : grades) sum += grade; // Суммируем оценки
        return sum / grades.size(); // Возвращаем среднее значение
    }

    // Метод для проверки, является ли студент отличником
    bool isExcellence() const {
        return average() == 5.0; 
    }

    // Метод для установки новых оценок
    void setGrades(const vector<int>& newGrades) {
        grades = newGrades; // Изменяем оценки студента
    }

    // Метод для получения оценок студента
    vector<int> getGrades() const {
        return grades; 
    }
};

// Функция для получения целого числа от пользователя
int inputInteger() {
    int number;
    while (true) { 
        cin >> number; // Считываем введенное значение
        if (cin.fail()) { // Проверяем, произошло ли исключение
            cin.clear(); // Очищаем состояние потока
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорируем неправильный ввод
            cout << "Некорректный ввод. Пожалуйста, введите целое число: "; 
        } else {
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорируем остаток строки
            return number; 
        }
    }
}

// Проверка на валидность имени 
bool isValidName(const string& name) {
    regex pattern("^[А-Яа-яЁё]+$"); // Регулярное выражение для проверки имени
    return regex_match(name, pattern); // Возвращаем результат проверки
}

// Проверка на валидность оценки
bool isValidGrade(int grade) {
    return grade >= 2 && grade <= 5;
}

// Главное меню
void menu() {
    cout << "Выберите задачу (1-6):\n";
    cout << "1. Точка\n";
    cout << "2. Прямая\n";
    cout << "3. Студент\n";
    cout << "4. Создаем точки\n";
    cout << "5. Создаем Студента\n";
    cout << "6. Студент отличник\n";
    cout << "0. Выйти\n";
}
int main() {
    while (true) { 
        menu(); 
        int choice = inputInteger(); // Получаем выбор пользователя

        if (choice == 0) break;

        switch (choice) { // Обработка выбора пользователя
            case 1: {
                vector<Point> points; // Вектор для хранения точек

                while (points.size() < 3) { 
                    int x, y; 
                    cout << "Введите координаты точки " << (points.size() + 1) << " (x, y): "; 
                    x = inputInteger(); 
                    y = inputInteger(); 

                    Point newPoint(x, y); // Создание новой точки

                    // Проверка на уникальность точки
                    bool unique = true; // Флаг для проверки уникальности
                    for (const auto& point : points) { // Проходим по всем введенным точкам
                        if (point.print() == newPoint.print()) { 
                            unique = false; // 
                            break;
                        }
                    }

                    if (!unique) { // Если точка не уникальна
                        cout << "Точки должны быть с разными координатами. Повторите попытку.\n"; 
                        continue; 
                    }

                    points.emplace_back(newPoint); // Добавляем точку в вектор
                }

                cout << "Введенные точки:\n"; 
                for (const auto& point : points) {
                    cout << point.print() << endl; 
                }
                break;
            }

            case 2: { // Создание и вывод линий
                cout << "Создание линий на двумерной плоскости:\n";
                Line line1(Point(1, 3), Point(23, 8)); 
                Line line2(Point(5, 10), Point(25, 10)); 
                Line line3(Point(1, 3), Point(25, 10)); 

                cout << line1.print() << endl; // Вывод 1 линии
                cout << line2.print() << endl; // Вывод 2 линии
                cout << line3.print() << endl; // Вывод 3 линии

                line1.setStart(Point(2, 4)); // Изменение начальной точки первой линии
                line1.setEnd(Point(20, 5)); // Изменение конечной точки первой линии
                line2.setStart(Point(6, 11)); // Изменение начальной точки второй линии
                line2.setEnd(Point(30, 11)); // Изменение конечной точки второй линии

                line3.setStart(line1.getStart()); // Установка начальной точки третьей линии как начальной первой линии
                line3.setEnd(line2.getEnd()); // Установка конечной точки третьей линии как конечной второй линии

                cout << "\nПосле изменения координат линий:\n"; 
                cout << line1.print() << endl; 
                cout << line2.print() << endl; 
                cout << line3.print() << endl; 

                line1.setStart(Point(3, 5)); // Изменение начальной точки первой линии

                cout << "\nПосле изменения координат первой линии:\n"; 
                cout << line1.print() << endl; 
                cout << line2.print() << endl; 
                cout << line3.print() << endl; 

                break;
            }
            case 3: { // Работа со студентами
                vector<int> vasyaGrades = {3, 4, 5}; // Оценки Васи
                Student vasya("Вася", vasyaGrades); // Создаем студента Васю
                Student petya("Петя", vasya.getGrades()); // Создаем студента Петю с теми же оценками, что и у Васи
                vector<int> petyaGrades = petya.getGrades(); // Получаем оценки Пети
                petyaGrades[0] = 5; // Изменяем первую оценку на 5
                petya.setGrades(petyaGrades); // Устанавливаем новые оценки Пети

                cout << "Студенты:\n";
                cout << vasya.print() << endl; 
                cout << petya.print() << endl; 

                Student andrei("Андрей", vasya.getGrades()); // Создаем нового студента Андрея с теми же оценками, что и у Васи

                cout << "Создан студент " << andrei.print() << endl; 

                cout << "Изменение оценок Васи...\n"; 
                vasyaGrades[0] = 2; // Устанавливаем первую оценку Васи на 2
                vasya.setGrades(vasyaGrades); // Применяем новые оценки

                cout << "Текущие оценки студентов после изменения:\n"; 
                cout << vasya.print() << endl; 
                cout << andrei.print() << endl; 
                break;
            }
            case 4: { // Создание 3 точек
                cout << "Введите координаты 3 точек:\n";
                vector<Point> uniquePoints; // Вектор для хранения точек

                while (uniquePoints.size() < 3) { // Запрос точек
                    int x, y; 
                    cout << "Введите координаты точки " << (uniquePoints.size() + 1) << " (x, y): "; 
                    x = inputInteger(); 
                    y = inputInteger(); 

                    Point newPoint(x, y); // Создание новой точки

                    // Проверка на уникальность точки
                    bool unique = true; 
                    for (const auto& point : uniquePoints) { // Проходим по всем введенным точкам
                        if (point.print() == newPoint.print()) { // Сравниваем
                            unique = false; // Точка не уникальна
                            break;
                        }
                    }

                    if (!unique) { // Если точка не уникальна
                        cout << "Точки должны быть с разными координатами. Повторите попытку.\n"; 
                        continue; // 
                    }

                    uniquePoints.emplace_back(newPoint); 
                }

                cout << "Введенные уникальные точки:\n"; 
                for (const auto& point : uniquePoints) {
                    cout << point.print() << endl; 
                }
                break;
            }

            case 5: { // Создание студента с именем и оценками
                string name; // Переменная для хранения имени студента
                cout << "Введите имя первого студента: "; 

                while (true) { 
                    getline(cin, name); // Считываем значение имени целиком
                    if (isValidName(name)) { // Проверяем имя на валидность
                        break; 
                    } else {
                        cout << "Некорректное имя. Повторите попытку: "; 
                    }
                }

                vector<int> grades(3); // Вектор для хранения оценок студента
                cout << "Введите 3 оценки для " << name << ". "; 
                for (int i = 0; i < 3; i++) { 
                    do {
                        cout << "Оценка " << (i + 1) << " для " << name << " (от 2 до 5): ";
                        grades[i] = inputInteger();
                    } while (!isValidGrade(grades[i])); // Проверяем каждую оценку
                }
                

                Student studentWithGrades(name, grades); // Создаем студента с введенным именем и оценками
                cout << studentWithGrades.print() << endl; // Выводим информацию о созданном студенте

                
                cout << "Введите имя второго студента: "; 
                string secondName; // Переменная для хранения имени второго студента
                while (true) { 
                    getline(cin, secondName); // Считываем значение имени целиком
                    if (isValidName(secondName)) { // Проверяем имя на валидность
                        break; 
                    } else {
                        cout << "Некорректное имя. Повторите попытку: "; 
                    }
                }

                
                Student studentWithoutGrades(secondName); // Создаем второго студента без оценок
                cout << studentWithoutGrades.print() << endl; // Выводим второго студента без оценок
                
                break;
            }
            
            case 6: { // Создание двух студентов и вывод информации об их средних баллах и статусе отличника
                
                string firstName;
                cout << "Введите имя первого студента: "; 
                while (true) { 
                    getline(cin, firstName); // Считываем значение имени целиком
                    if (isValidName(firstName)) { 
                        break; 
                    } else {
                        cout << "Некорректное имя. Повторите попытку: "; 
                    }
                }

                vector<int> firstGrades(4); // Оценки для первого студента
                cout << "Введите 4 оценки для " << firstName << ". ";
                for (int i = 0; i < 4; i++) {
                    do {
                        cout << "Оценка " << (i + 1) << " для " << firstName << " (от 2 до 5): ";
                        firstGrades[i] = inputInteger();
                    } while (!isValidGrade(firstGrades[i])); // Проверяем каждую оценку
                }
               
                Student firstStudent(firstName, firstGrades); // Создаем первого студента

               
                string secondName; 
                cout << "Введите имя второго студента: "; 
                while (true) { 
                    getline(cin, secondName); // Считываем значение имени целиком
                    if (isValidName(secondName)) {
                        break; 
                    } else {
                        cout << "Некорректное имя. Повторите попытку: "; 
                    }
                }

                vector<int> secondGrades(4); 
                cout << "Введите 4 оценки для " << secondName << ". "; 
                for (int i = 0; i < 4; i++) { 
                    do {
                        cout << "Оценка " << (i + 1) << " для " << secondName << " (от 2 до 5): ";
                        secondGrades[i] = inputInteger();
                    } while (!isValidGrade(secondGrades[i])); // Проверяем каждую оценку
                }
                Student secondStudent(secondName, secondGrades); // Создаем второго студента

                // Выводим информацию о среднем балле и статусе отличника
                cout << "\nИнформация о студентах:\n";
                cout << firstStudent.print() << " Средний балл: " << fixed << setprecision(2) << firstStudent.average() 
                     << ", Отличник: " << (firstStudent.isExcellence() ? "Да" : "Нет") << endl; // Информация о первом студенте
                cout << secondStudent.print() << " Средний балл: " << fixed << setprecision(2) << secondStudent.average() 
                     << ", Отличник: " << (secondStudent.isExcellence() ? "Да" : "Нет") << endl; // Информация о втором студенте

                break;
            }
        }
    }
    return 0; 
}
