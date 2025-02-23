#include <iostream> 
#include <fstream>  
#include <string>   
#include <algorithm> 
#include <vector>   
#include <set>     
#include <map>      
#include <sstream>

using namespace std; 

// Функция для проверки, является ли строка числом
bool isNumber(const string& str) {
    for (char const &c : str) { // Проход по каждому символу строки
        if (isdigit(c) == 0) return false; // Если символ не цифра, возвращаем false
    }
    return true; 
}


// Задание 1: Однонаправленный список
template <typename T> // Шаблон для работы с любым типом данных
class SinglyLinkedList { 
private:
    struct Node { // Структура для узла списка
        T data; // Данные узла
        Node* next; 
    };

    Node* head; 

public:
    SinglyLinkedList() : head(nullptr) {} // Конструктор, инициализирующий пустой список

    ~SinglyLinkedList() { // Деструктор для очистки памяти
        Node* current = head; // Начинаем с первого узла
        while (current) { // Пока есть узлы
            Node* next = current->next; // Сохраняем следующий узел
            delete current; // Удаляем текущий узел
            current = next; // Переходим к следующему узлу
        }
    }

    void add(T data) { // Метод для добавления элемента в конец списка
        Node* newNode = new Node{ data, nullptr }; 
        if (!head) { // Если список пуст
            head = newNode; // Новый узел становится первым
        } else 
            Node* current = head; // Начинаем с первого узла
            while (current->next) { // Пока есть следующий узел
                current = current->next; // Переходим к следующему узлу
            }
            current->next = newNode; // Добавляем новый узел в конец
        }
    }

    bool remove(T data) { // Метод для удаления элемента из списка
        if (!head) return false; 

        if (head->data == data) { // Если первый элемент равен данным
            Node* temp = head; // Сохраняем первый узел
            head = head->next; // Переходим ко второму узлу
            delete temp; // Удаляем первый узел
            return true; // Возвращаем true, так как элемент удален
        }

        Node* current = head; // Начинаем с первого узла
        while (current->next) { // Пока есть следующий узел
            if (current->next->data == data) { // Если следующий элемент равен данным
                Node* temp = current->next; // Сохраняем следующий узел
                current->next = current->next->next; // Пропускаем следующий узел
                delete temp; 
                return true; 
            }
            current = current->next; // Переходим к следующему узлу
        }

        return false; // Возвращаем false, так как элемент не найден
    }

    void print() const { // Метод для вывода списка на экран
        Node* current = head; // Начинаем с первого узла
        while (current) { // Пока есть узлы
            cout << current->data << " "; // Выводим данные узла
            current = current->next; 
        }
        cout << endl; // Переход на новую строку
    }

    // Дополнительно для задачи 1: Переворот списка
    void reverse() { // Метод для переворота списка
        Node* prev = nullptr; // Предыдущий узел
        Node* current = head; // Текущий узел
        Node* next = nullptr; // Следующий узел

        while (current) { // Пока есть узлы
            next = current->next; // Сохраняем следующий узел
            current->next = prev; // Переворачиваем указатель на следующий узел
            prev = current; // Переходим к следующему узлу
            current = next; // Переходим к следующему узлу
        }

        head = prev; // Обновляем указатель на первый узел
    }

    Node* getHead() const { // Метод для получения первого узла
        return head; 
    }

    void setHead(Node* newHead) { // Метод для установки нового первого узла
        head = newHead; 
    }
};


// Задание 2: Двунаправленный список

template <typename T> 
class DoublyLinkedList { // Класс для двунаправленного списка
private:
    struct Node { // Структура для узла списка
        T data; // Данные узла
        Node* next; 
        Node* prev; 
    };

    Node* head; 
    Node* tail; 

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {} // Конструктор, инициализирующий пустой список

    ~DoublyLinkedList() { // Деструктор для очистки памяти
        Node* current = head; // Начинаем с первого узла
        while (current) { // Пока есть узлы
            Node* next = current->next; // Сохраняем следующий узел
            delete current; 
            current = next; 
        }
    }

    void add(T data) { // Метод для добавления элемента в конец списка
        Node* newNode = new Node{ data, nullptr, nullptr }; // Создаем новый узел
        if (!head) { // Если список пуст
            head = newNode; // Новый узел становится первым
            tail = newNode; // Новый узел становится последним
        } else { // Если список не пуст
            newNode->prev = tail; // Новый узел указывает на последний узел
            tail->next = newNode; // Последний узел указывает на новый узел
            tail = newNode; // Новый узел становится последним
        }
    }

    bool remove(T data) { // Метод для удаления элемента из списка
        if (!head) return false; // Если список пуст, возвращаем false

        if (head->data == data) { // Если первый элемент равен данным
            Node* temp = head; // Сохраняем первый узел
            head = head->next; // Переходим ко второму узлу
            if (head) head->prev = nullptr; // Если второй узел существует, обнуляем его предыдущий указатель
            else tail = nullptr; // Если второго узла нет, обнуляем указатель на последний узел
            delete temp; 
            return true; 
        }

        Node* current = head; // Начинаем с первого узла
        while (current) { // Пока есть узлы
            if (current->data == data) { // Если текущий элемент равен данным
                if (current->prev) current->prev->next = current->next; // Если есть предыдущий узел, обновляем его следующий указатель
                if (current->next) current->next->prev = current->prev; // Если есть следующий узел, обновляем его предыдущий указатель
                if (current == tail) tail = current->prev; // Если текущий узел последний, обновляем указатель на последний узел
                delete current; 
                return true; //
            }
            current = current->next; // Переходим к следующему узлу
        }

        return false; 
    }

    void print() const { // Метод для вывода списка на экран
        Node* current = head; // Начинаем с первого узла
        while (current) { // Пока есть узлы
            cout << current->data << " "; // Выводим данные узла
            current = current->next; // Переходим к следующему узлу
        }
        cout << endl; 
    }

    // Дополнительно для задачи 2: Вставка элемента справа и слева от E
    void insertAround(T e, T f) { // Метод для вставки элемента справа и слева от E
        Node* current = head; 
        while (current) { 
            if (current->data == e) { // Если текущий элемент равен E
                // Вставка справа
                Node* newNodeRight = new Node{ f, current->next, current }; // Создаем новый узел справа
                if (current->next) { // Если есть следующий узел
                    current->next->prev = newNodeRight; // Обновляем предыдущий указатель следующего узла
                } else { 
                    tail = newNodeRight; // Новый узел становится последним
                }
                current->next = newNodeRight; // Обновляем следующий указатель текущего узла

                // Вставка слева
                Node* newNodeLeft = new Node{ f, current, current->prev }; // Создаем новый узел слева
                if (current->prev) { // Если есть предыдущий узел
                    current->prev->next = newNodeLeft; // Обновляем следующий указатель предыдущего узла
                } else { 
                    head = newNodeLeft; // Новый узел становится первым
                }
                current->prev = newNodeLeft; 
                return; // Предполагаем, что E встречается 1 раз
            }
            current = current->next; // Переходим к следующему узлу
        }
        cout << "Элемент E не найден в списке." << endl; 
    }
};


// Задание 3 и 4: Неупорядоченный список с уникальными элементами

template <typename T> 
class UniqueList { // Класс для неупорядоченного списка с уникальными элементами
private:
    set<T> data; // Множество для хранения уникальных элементов

public:
    bool add(T element) { // Метод для добавления элемента в список
        return data.insert(element).second; // Возвращает true, если элемент был добавлен (уникальный)
    }

    bool remove(T element) { // Метод для удаления элемента из списка
        return data.erase(element) > 0; // Возвращает true, если элемент был удален
    }

    UniqueList<T> Union(const UniqueList<T>& other) const { // Метод для объединения списков
        UniqueList<T> result = *this; // Создаем копию текущего списка
        for (const auto& element : other.data) { // Проходим по элементам другого списка
            result.data.insert(element); // Добавляем элементы в результат
        }
        return result; 
    }

    UniqueList<T> Except(const UniqueList<T>& other) const { // Метод для исключения элементов другого списка
        UniqueList<T> result = *this; // Создаем копию текущего списка
        for (const auto& element : other.data) { // Проходим по элементам другого списка
            result.data.erase(element); // Удаляем элементы из результата
        }
        return result; 
    }

    UniqueList<T> Intersect(const UniqueList<T>& other) const { // Метод для пересечения списков
        UniqueList<T> result; // Создаем пустой список для результата
        for (const auto& element : data) { // Проходим по элементам текущего списка
            if (other.Contains(element)) { // Если элемент содержится в другом списке
                result.add(element); // Добавляем элемент в результат
            }
        }
        return result; 
    }

    bool Contains(const T& element) const { // Метод для проверки наличия элемента в списке
        return data.count(element) > 0; // Возвращает true, если элемент найден
    }

    void print() const { // Метод для вывода списка на экран
        for (const auto& element : data) { // Проходим по элементам списка
            cout << element << " "; // Выводим элемент
        }
        cout << endl; 
    }
};


// Задание 5: Словарь

template <typename K, typename V> 
class Dictionary { 
private:
    map<K, V> data; // Ассоциативный массив для хранения пар ключ-значение

public:
    bool add(const K& key, const V& value) { // Метод для добавления пары ключ-значение
        return data.insert({ key, value }).second; // Возвращает true, если ключ уникален и вставка прошла успешно
    }

    bool remove(const K& key) { // Метод для удаления пары ключ-значение
        return data.erase(key) > 0; // Возвращает true, если пара удалена
    }

    V* get(const K& key) { // Метод для получения значения по ключу
        auto it = data.find(key); // Ищем пару по ключу
        if (it != data.end()) { // Если пара найдена
            return &it->second; // Возвращаем указатель на значение
        }
        return nullptr; 
    }

    void print() const { // Метод для вывода словаря на экран
        for (const auto& pair : data) { // Проходим по парам словаря
            cout << pair.first << ": " << pair.second << endl; // Выводим ключ и значение
        }
    }
};


// Реализация задач

// Задача 1: Переворот списка
void task1() { 
    SinglyLinkedList<int> list; 
    int n, value; // Переменные для количества элементов и значения
    string input; // Переменная для ввода строки

    cout << "Введите количество элементов списка: "; 
    cin >> input; 
    while (!isNumber(input)) { 
        cout << "Ошибка: введено не число. Попробуйте снова: "; 
        cin >> input; 
    }
    n = stoi(input); // Преобразуем строку в число

    cout << "Введите элементы списка:" << endl; 
    for (int i = 0; i < n; ++i) { // Проходим по количеству элементов
        cin >> input; 
        while (!isNumber(input)) { 
            cout << "Ошибка: введено не число. Попробуйте снова: "; 
            cin >> input; 
        }
        value = stoi(input); // Преобразуем строку в число
        list.add(value); // Добавляем элемент в список
    }

    cout << "Исходный список: "; 
    list.print(); 

    list.reverse(); 

    cout << "Перевернутый список: "; 
    list.print(); 
}

// Задача 2: Вставка элемента в двунаправленный список
void task2() { 
    DoublyLinkedList<int> list; 
    int n, value, e, f; 
    string input; 

    cout << "Введите количество элементов списка: "; 
    cin >> input; 
    while (!isNumber(input)) { 
        cout << "Ошибка: введено не число. Попробуйте снова: "; 
        cin >> input; 
    }
    n = stoi(input); 

    cout << "Введите элементы списка:" << endl; 
    for (int i = 0; i < n; ++i) { // Проходим по количеству элементов
        cin >> input; 
        while (!isNumber(input)) { 
            cout << "Ошибка: введено не число. Попробуйте снова: "; 
            cin >> input; 
        }
        value = stoi(input); // Преобразуем строку в число
        list.add(value); // Добавляем элемент в список
    }

    cout << "Введите элемент E: "; 
    cin >> input; 
    while (!isNumber(input)) { 
        cout << "Ошибка: введено не число. Попробуйте снова: "; 
        cin >> input;
    }
    e = stoi(input); // Преобразуем строку в число

    cout << "Введите элемент F: "; 
    cin >> input; 
    while (!isNumber(input)) { 
        cout << "Ошибка: введено не число. Попробуйте снова: "; 
        cin >> input; // Считываем строку
    }
    f = stoi(input); // Преобразуем строку в число

    cout << "Исходный список: "; 
    list.print();

    list.insertAround(e, f); 

    cout << "Измененный список: "; 
    list.print(); 
}

// Задача 3
void task3() { 
    int numStudents, numDiscos; // Переменные для количества студентов и дискотек
    string input; // Переменная для ввода строки

    cout << "Введите количество студентов: "; 
    cin >> input; 
    while (!isNumber(input)) { 
        cout << "Ошибка: введено не число. Попробуйте снова: "; 
        cin >> input; 
    }
    numStudents = stoi(input); 

    cout << "Введите количество дискотек: "; 
    cin >> input; 
    while (!isNumber(input)) { 
        cout << "Ошибка: введено не число. Попробуйте снова: "; 
        cin >> input; 
    }
    numDiscos = stoi(input); 

    cin.ignore(); // Игнорируем символ новой строки после ввода чисел

    // Ввод перечня дискотек
    vector<string> discos(numDiscos); // Вектор для хранения названий дискотек
    cout << "Введите названия дискотек:" << endl; 
    for (int i = 0; i < numDiscos; ++i) { // Проходим по количеству дискотек
        getline(cin, discos[i]); // Считываем строку с названием дискотеки
    }

    // Множество всех дискотек
    UniqueList<string> allDiscosList; // Создаем список для всех дискотек
    for (const auto& disco : discos) { // Проходим по названиям дискотек
        allDiscosList.add(disco); // Добавляем дискотеку в список
    }

    // Ввод посещенных дискотек каждым студентом
    vector<UniqueList<string>> studentDiscos(numStudents); // Вектор для хранения списков дискотек каждого студента
    for (int i = 0; i < numStudents; ++i) { // Проходим по количеству студентов
        cout << "Введите дискотеки, которые посетил студент " << i + 1 << " (через запятую):" << endl; 
        string line; // Переменная для ввода строки
        getline(cin, line); 
        string disco; // Переменная для названия дискотеки
        for (size_t j = 0; j <= line.length(); ++j) { // Проходим по символам строки
            if (line[j] == ',' || j == line.length()) { // Если символ запятая или конец строки
                studentDiscos[i].add(disco); // Добавляем дискотеку в список студента
                disco.clear(); // Очищаем переменную для названия дискотеки
            } else { // Если символ не запятая
                disco += line[j]; // Добавляем символ к названию дискотеки
            }
        }
    }

    // 1. Дискотеки, которые посетили все студенты
    UniqueList<string> allVisitedDiscos = allDiscosList; // Создаем копию списка всех дискотек
    for (const auto& studentDiscoList : studentDiscos) { // Проходим по спискам дискотек студентов
        allVisitedDiscos = allVisitedDiscos.Intersect(studentDiscoList); // Пересекаем списки
    }

    cout << "\nДискотеки, которые посетили все студенты:" << endl; 
    allVisitedDiscos.print(); // Выводим список дискотек на экран

    // 2. Дискотеки, которые посетили некоторые студенты
    UniqueList<string> someVisitedDiscos; // Создаем пустой список для дискотек, которые посетили некоторые студенты
    for (const auto& studentDiscoList : studentDiscos) { // Проходим по спискам дискотек студентов
        someVisitedDiscos = someVisitedDiscos.Union(studentDiscoList); // Объединяем списки
    }

    cout << "\nДискотеки, которые посетили некоторые студенты:" << endl; 
    someVisitedDiscos.print(); // Выводим список дискотек на экран

    // 3. Дискотеки, которые не посетил ни один студент
    UniqueList<string> notVisitedDiscos = allDiscosList.Except(someVisitedDiscos); // Исключаем дискотеки, которые посетили некоторые студенты

    cout << "\nДискотеки, которые не посетил ни один студент:" << endl; 
    notVisitedDiscos.print(); 
}

// Задача 4: Алфавитный порядок символов в словах с четными номерами
void task4() { 
    ifstream file("4.txt"); 
    if (!file.is_open()) { 
        cout << "Ошибка открытия файла 4.txt" << endl; 
        return; /
    }

    string word; // Переменная для слова
    int wordNumber = 1; // Переменная для номера слова
    set<char> characters; // Множество для хранения уникальных символов

    while (file >> word) { // Пока есть слова в файле
        if (wordNumber % 2 == 0) { 
            for (char c : word) { // Проходим по символам слова
                characters.insert(tolower(c)); // Добавляем символ в множество в нижнем регистре
            }
        }
        wordNumber++; // Увеличиваем номер слова
    }

    cout << "Символы, встречающиеся в словах с четными номерами (в алфавитном порядке):" << endl; 
    for (char c : characters) { // Проходим по символам множества
        cout << c << " "; 
    }
    cout << endl; 

    file.close(); 
}

// Задача 5: Абитуриенты, допущенные к экзаменам
void task5() { 
    ifstream file("5.txt"); 
    if (!file.is_open()) { 
        cout << "Ошибка открытия файла 5.txt" << endl; 
        return; 
    }

    vector<pair<string, string>> eligibleApplicants; // Вектор для хранения пар фамилия-имя абитуриентов
    string line; // Переменная для строки

    while (getline(file, line)) { // Пока есть строки в файле
        string lastName, firstName; // Переменные для фамилии и имени
        int score1, score2, score3; // Переменные для баллов

        size_t firstSpace = line.find(' '); // Ищем первый пробел
        if (firstSpace == string::npos) continue; // Если пробел не найден, пропускаем строку
        lastName = line.substr(0, firstSpace); // Извлекаем фамилию

        size_t secondSpace = line.find(' ', firstSpace + 1); // Ищем второй пробел
        if (secondSpace == string::npos) continue; // Если пробел не найден, пропускаем строку
        firstName = line.substr(firstSpace + 1, secondSpace - firstSpace - 1); // Извлекаем имя

        string scores = line.substr(secondSpace + 1); // Извлекаем строку с баллами
        stringstream ss(scores); // Создаем поток строк для чтения баллов
        ss >> score1 >> score2 >> score3; // Считываем баллы

        if (score1 >= 30 && score2 >= 30 && score3 >= 30 && (score1 + score2 + score3) >= 140) { 
            eligibleApplicants.push_back({ lastName, firstName }); // Добавляем пару фамилия-имя в вектор
        }
    }

    // Сортировка по фамилии
    sort(eligibleApplicants.begin(), eligibleApplicants.end()); // Сортируем вектор по фамилии

    cout << "Абитуриенты, допущенные к сдаче экзаменов в первом потоке (в алфавитном порядке фамилий):" << endl; 
    for (const auto& applicant : eligibleApplicants) { // Проходим по парам вектора
        cout << applicant.first << " " << applicant.second << endl; // Выводим фамилию и имя
    }

    file.close(); 
}

int main() { 
    int choice; // Переменная для выбора задачи
    string input; // Переменная для ввода строки

    do { 
        cout << "\nМеню:" << endl; 
        cout << "1. Задание 1: Переворот однонаправленного списка" << endl; 
        cout << "2. Задание 2: Вставка элемента в двунаправленный список" << endl; 
        cout << "3. Задание 3: Анализ посещения дискотек студентами" << endl; 
        cout << "4. Задание 4: Алфавитный порядок символов в словах с четными номерами (из файла 4.txt)" << endl; 
        cout << "5. Задание 5: Абитуриенты, допущенные к экзаменам (из файла 5.txt)" << endl; 
        cout << "0. Выход" << endl; 
        cout << "Выберите задание: "; 
        cin >> input; 
        while (!isNumber(input)) { 
            cout << "Ошибка: введено не число. Попробуйте снова: "; 
            cin >> input; 
        choice = stoi(input); 

        switch (choice) { 
            case 1:
                task1(); 
                break;
            case 2:
                task2(); 
                break;
            case 3:
                task3(); 
                break;
            case 4:
                task4(); 
                break;
            case 5:
                task5(); 
                break;
            case 0:
                cout << "Выход из программы." << endl; 
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова." << endl; 
        }
    } while (choice != 0); 

    return 0; 
}
