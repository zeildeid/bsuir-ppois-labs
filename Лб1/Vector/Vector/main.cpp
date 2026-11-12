#include <iostream>
#include <clocale>
#include "Vector.h"

using namespace std;

void showMenu() {
    cout << "\n--- МЕНЮ РАБОТЫ С ВЕКТОРОМ ---" << endl;
    cout << "1. Ввести вектор A (x1 y1 z1 x2 y2 z2)" << endl;
    cout << "2. Ввести вектор B (x1 y1 z1 x2 y2 z2)" << endl;
    cout << "3. Вывести векторы A и B и их длины" << endl;
    cout << "4. Сложить векторы (A + B)" << endl;
    cout << "5. Вычесть векторы (A - B)" << endl;
    cout << "6. Векторное произведение (A * B)" << endl;
    cout << "7. Умножить и разделить вектор A на число" << endl;
    cout << "8. Найти косинус угла между A и B" << endl;
    cout << "9. Сравнить векторы A и B" << endl;
    cout << "0. Выход" << endl;
    cout << "Ваш выбор: ";
}

int main() {
    setlocale(LC_ALL, "Russian");

    Vector a(0, 0, 0, 3, 4, 0);
    Vector b(0, 0, 0, 0, 5, 12);

    int choice = -1;
    while (choice != 0) {
        showMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Некорректный ввод! Попробуйте снова." << endl;
            continue;
        }

        try {
            if (choice == 1) {
                cout << "Введите 6 координат для вектора A: ";
                a.read(cin);
            }
            else if (choice == 2) {
                cout << "Введите 6 координат для вектора B: ";
                b.read(cin);
            }
            else if (choice == 3) {
                cout << "Вектор A: " << a.toString() << " | Длина: " << a.length() << endl;
                cout << "Вектор B: " << b.toString() << " | Длина: " << b.length() << endl;
                cout << "Всего векторов в памяти: " << Vector::getCount() << endl;
            }
            else if (choice == 4) {
                Vector c = a + b;
                cout << "A + B = " << c.toString() << endl;
            }
            else if (choice == 5) {
                Vector c = a - b;
                cout << "A - B = " << c.toString() << endl;
            }
            else if (choice == 6) {
                Vector c = a * b;
                cout << "A * B = " << c.toString() << endl;
            }
            else if (choice == 7) {
                double num;
                cout << "Введите число: ";
                cin >> num;
                cout << "A * num = " << (a * num).toString() << endl;
                cout << "A / num = " << (a / num).toString() << endl;
            }
            else if (choice == 8) {
                cout << "Косинус угла между A и B: " << a.cosAngle(b) << endl;
            }
            else if (choice == 9) {
                cout << "A == B: " << (a == b ? "Да" : "Нет") << endl;
                cout << "A != B: " << (a != b ? "Да" : "Нет") << endl;
                cout << "A >  B: " << (a > b ? "Да" : "Нет") << endl;
                cout << "A >= B: " << (a >= b ? "Да" : "Нет") << endl;
                cout << "A <  B: " << (a < b ? "Да" : "Нет") << endl;
                cout << "A <= B: " << (a <= b ? "Да" : "Нет") << endl;
            }
            else if (choice == 0) {
                cout << "Выход из программы." << endl;
            }
            else {
                cout << "Нет такого пункта меню!" << endl;
            }
        }
        catch (const char* msg) {
            cout << msg << endl;
        }
    }

    return 0;
}