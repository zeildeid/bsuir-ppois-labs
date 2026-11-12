#include <iostream>
#include <clocale>
#include "Set.h"

using namespace std;

void showMenu() {
    cout << "\n--- МЕНЮ РАБОТЫ С МНОЖЕСТВОМ ---" << endl;
    cout << "1. Ввести множество A из строки (например: {a, b, {c}})" << endl;
    cout << "2. Ввести множество B из строки" << endl;
    cout << "3. Показать множества A и B (мощность и проверка на пустоту)" << endl;
    cout << "4. Добавить элемент в множество A" << endl;
    cout << "5. Удалить элемент из множества A" << endl;
    cout << "6. Проверить принадлежность элемента множеству A (оператор [])" << endl;
    cout << "7. Объединение множеств (A + B)" << endl;
    cout << "8. Пересечение множеств (A * B)" << endl;
    cout << "9. Разность множеств (A - B)" << endl;
    cout << "10. Построить булеан множества A" << endl;
    cout << "11. Сравнить множества A и B (==, !=)" << endl;
    cout << "0. Выход" << endl;
    cout << "Ваш выбор: ";
}

int main() {
    setlocale(LC_ALL, "Russian");

    Set setA("{a, b, {a, b}}");
    Set setB("{b, c, {}}");

    int choice = -1;
    while (choice != 0) {
        showMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Ошибка ввода! Введите номер пункта." << endl;
            continue;
        }
        cin.ignore();

        if (choice == 1) {
            cout << "Введите множество A: ";
            cin >> setA;
        }
        else if (choice == 2) {
            cout << "Введите множество B: ";
            cin >> setB;
        }
        else if (choice == 3) {
            cout << "Множество A = " << setA
                << " | Мощность: " << setA.cardinality()
                << " | Пустое: " << (setA.isEmpty() ? "Да" : "Нет") << endl;
            cout << "Множество B = " << setB
                << " | Мощность: " << setB.cardinality()
                << " | Пустое: " << (setB.isEmpty() ? "Да" : "Нет") << endl;
        }
        else if (choice == 4) {
            string elem;
            cout << "Введите элемент для добавления (например, d или {x, y}): ";
            getline(cin, elem);
            setA.add(elem);
            cout << "Теперь A = " << setA << endl;
        }
        else if (choice == 5) {
            string elem;
            cout << "Введите элемент для удаления: ";
            getline(cin, elem);
            setA.remove(elem);
            cout << "Теперь A = " << setA << endl;
        }
        else if (choice == 6) {
            string elem;
            cout << "Введите элемент для поиска в A: ";
            getline(cin, elem);
            if (setA[elem]) {
                cout << "Элемент ПРИНАДЛЕЖИТ множеству A." << endl;
            }
            else {
                cout << "Элемент НЕ принадлежит множеству A." << endl;
            }
        }
        else if (choice == 7) {
            Set res = setA + setB;
            cout << "A + B = " << res << endl;
        }
        else if (choice == 8) {
            Set res = setA * setB;
            cout << "A * B = " << res << endl;
        }
        else if (choice == 9) {
            Set res = setA - setB;
            cout << "A - B = " << res << endl;
        }
        else if (choice == 10) {
            Set b = setA.boolean();
            cout << "Булеан P(A) (мощность " << b.cardinality() << "): " << b << endl;
        }
        else if (choice == 11) {
            cout << "A == B: " << (setA == setB ? "Да" : "Нет") << endl;
            cout << "A != B: " << (setA != setB ? "Да" : "Нет") << endl;
        }
        else if (choice == 0) {
            cout << "Выход из программы." << endl;
        }
        else {
            cout << "Неверный пункт меню!" << endl;
        }
    }

    return 0;
}