#include <iostream>
#include <Windows.h>
#include <string>
#include <stdlib.h>
#include <cctype>
#include <conio.h>
#include <random>
#include <algorithm>
#include <iomanip>
#include <cmath>

#define PI 3.14159265

using namespace std;
HANDLE handleConsole;

enum ConsoleColor
{
    Blue = 1,
    Green = 2,
    Red = 4,
    Yellow = 14,
    White = 15
};

class MyInput {

    public: 

        double InputData(string text){

            string xStr = "";

            bool isNumber = false;
            double x = 0;

            while (true) {
                cout << text;

                cin >> xStr;
                isNumber = isalpha(atoi(xStr.c_str()));

                if (!isNumber){
                    SetConsoleTextAttribute(handleConsole, Red);
                    cout << xStr + " - не число!";
                }
                else if(atof(xStr.c_str()) <= 0) {
                    SetConsoleTextAttribute(handleConsole, Red);
                    cout << "Число должно быть больше нуля!";
                }
                else
                    break;
            }

            return atof(xStr.c_str());
    }
};

class MyRandom {
    
    public:
        double MIN_RANDOM = 2, MAX_RANDOM = 1000;

        bool isRandomData() {
            cout << "Сгенерировать данные случайным образом [y/n]?" << endl;

            string answer;
            getline(cin, answer);

            transform(answer.begin(), answer.end(), answer.begin(), tolower);

            return answer == "y" || answer == "";
        }

        double GetRandom(int min, int max) {
            return rand() % (max - min) - min;
        }

};

class Task6 {

    private:
        double printVolume(double h, double r1, double r2) {

            cout << "v = ПИ * h (r1^2 - r2^2)" << endl;
            cout << "v = " << PI << " * " << h << "(" << fixed << r1 <<"^2 - " << fixed << r2 << "^2)" << endl;

            double square1 = r1 * r1;
            double square2 = r2 * r2;

            cout << "v = " << PI << " * " << h << " (" << fixed << square1 << " - " << fixed << square2 << ")" << endl;

            double differenceSquare = square1 - square2;
            cout << "v = " << PI << " * " << fixed << h << " * " << fixed << differenceSquare << endl;

            double result = PI * h * differenceSquare;
            cout << "v = " << fixed << result << endl;
            return result;
        }

    public:
        void Init() {

            HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(handleConsole, White);

            cout << "\nВычислить v (объём) полого цилиндра" << endl;
            cout << "высотой h" << endl;
            cout << "внешним радиусом r1" << endl;
            cout << "внутренним радиусом r2" << endl << endl;

            cout << "По формуле: v = ПИ * h (r1^2 - r2^2)" << endl << endl;

            double r1, r2, h;

            MyRandom myRandom = *new MyRandom();
            
            if (myRandom.isRandomData()) {
                r2 = myRandom.GetRandom(myRandom.MIN_RANDOM, myRandom.MAX_RANDOM) - 1;
                r1 = myRandom.GetRandom(r2, myRandom.MAX_RANDOM);
                h =  myRandom.GetRandom(myRandom.MIN_RANDOM, myRandom.MAX_RANDOM);
            }
            else {
                MyInput myInput = *new MyInput();

                h = myInput.InputData("Введите высоту цилиндра: ");

                while (true) {
                    SetConsoleTextAttribute(handle, 37);

                    r1 = myInput.InputData("Введите внешний радиус цилиндра: ");
                    r2 = myInput.InputData("Введите внутренний радиус цилиндра: ");

                    if (r1 <= r2) {
                        SetConsoleTextAttribute(handle, 4);
                        cout << "Внешний радиус цилиндра должен быть больше внутреннего!";
                    }
                    else
                        break;
                }
              
            }

            SetConsoleTextAttribute(handleConsole, Yellow);
            cout << "Полученные данные:" << endl;
            cout << "Высота цилиндра (h): " << h << endl;
            cout << "Внешний радиус цилиндра (r1): " << r1 << endl;
            cout << "Внутренний радиус цилиндра (r2): " << r2 << endl << endl;


            SetConsoleTextAttribute(handleConsole, Green);
            printVolume(h, r1, r2);

            SetConsoleTextAttribute(handleConsole, White);

        }  

};

class Task16 {

    private:
        double printSquare(double side, double height) {
            
            cout << "S = a * h" << endl;
            cout << "S = " << side << " * " << height << endl;
            
            double result = side * height;
            cout << "S = " << result << endl;

            return result;
        }

        double printSquareCorner(double side1, double side2, double corner) {

            cout << "S = a * b * sin(A)" << endl;
            cout << "S = " << side1 << " * " << side2 << " * sin(" << corner << ")" << endl;

            double sinCorner = sin(corner);

            cout << "S = " << side1 << " * " << side2 << " * " << sinCorner << endl;

            double result = side1 * side2 * sinCorner;

            cout << "S = " << result << endl;

            return result;
        }

        double printSquareDiagonals(double d1, double d2, double corner) {

            cout << "S = 0.5 * d1 * d2 * sin(A)" << endl;
            cout << "S = 0.5 * " << d1 << " * " << d2 << " * sin(" << corner << ")" << endl;

            double sinCorner = sin(corner);

            cout << "S = 0.5 * " << d1 << " * " << d2 << " * " << sinCorner << endl;

            double result = (d1 * d2 * sinCorner) / 2;

            cout << "S = " << result << endl;

            return result;
        }

    public:
        void InitSideHeight() {

            double side, height;

            MyRandom myRandom = *new MyRandom();

            if (myRandom.isRandomData()) {
                side = myRandom.GetRandom(myRandom.MIN_RANDOM, myRandom.MAX_RANDOM);
                height = myRandom.GetRandom(myRandom.MIN_RANDOM, myRandom.MAX_RANDOM);
            }
            else {
                MyInput myInput = *new MyInput();
                side = myInput.InputData("Введите сторону параллелограмма: ");
                height = myInput.InputData("Введите высоту параллелограмма: ");
            }

            SetConsoleTextAttribute(handleConsole, Yellow);
            cout << "Полученные данные:" << endl;
            cout << "Сторона параллелограмма (a): " << side << endl;
            cout << "Высота параллелограмма: (h): " << height << endl << endl;

            SetConsoleTextAttribute(handleConsole, Green);
            printSquare(side, height);

            SetConsoleTextAttribute(handleConsole, White);
        }

        void InitSidesCorner() {
            
            double side1, side2, corner;

            MyRandom myRandom = *new MyRandom();

            if (myRandom.isRandomData()) {
                side1 = myRandom.GetRandom(myRandom.MIN_RANDOM, myRandom.MAX_RANDOM);
                side2 = myRandom.GetRandom(myRandom.MIN_RANDOM, myRandom.MAX_RANDOM);
                corner = myRandom.GetRandom(myRandom.MIN_RANDOM, 89);
            }
            else {
                MyInput myInput = *new MyInput();
                side1 = myInput.InputData("Введите первую сторону параллелограмма (а): ");
                side2 = myInput.InputData("Введите вторую сторону параллелограмма (b): ");
                corner = myInput.InputData("Введите угол между сторонами а и b (A): ");
            }

            SetConsoleTextAttribute(handleConsole, Yellow);
            cout << "Полученные данные:" << endl;
            cout << "Первая сторона параллелограмма (а): " << side1 << endl;
            cout << "Вторая сторона параллелограмма (b): " << side2 << endl;
            cout << "Угол между сторонами а и b (A): " << corner << endl << endl;

            SetConsoleTextAttribute(handleConsole, Green);
            printSquareCorner(side1, side2, corner);

            SetConsoleTextAttribute(handleConsole, White);
        }

        void InitSidesDiagonals() {

            double d1, d2, corner;

            MyRandom myRandom = *new MyRandom();

            if (myRandom.isRandomData()) {
                d1 = myRandom.GetRandom(myRandom.MIN_RANDOM, myRandom.MAX_RANDOM);
                d2 = myRandom.GetRandom(myRandom.MIN_RANDOM, myRandom.MAX_RANDOM);
                corner = myRandom.GetRandom(myRandom.MIN_RANDOM, 89);
            }
            else {
                MyInput myInput = *new MyInput();
                d1 = myInput.InputData("Введите первую диагональ параллелограмма (d1): ");
                d2 = myInput.InputData("Введите вторую дигональ параллелограмма (d2): ");
                corner = myInput.InputData("Введите угол между диагоналями d1 и d2 (A): ");
            }

            SetConsoleTextAttribute(handleConsole, Yellow);
            cout << "Полученные данные:" << endl;
            cout << "Первая диагональ параллелограмма (d1): " << d1 << endl;
            cout << "Вторая диагональ параллелограмма (d2): " << d2 << endl;
            cout << "Угол между диагоналями d1 и d2 (A): " << corner << endl << endl;

            SetConsoleTextAttribute(handleConsole, Green);
            printSquareDiagonals(d1, d2, corner);

            SetConsoleTextAttribute(handleConsole, White);
        }

        void Init() {
            HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(handleConsole, White);

            bool isGo = true;

            while (isGo)
            {
                cout << "\nВычислить S (площадь) параллелограмма" << endl;
                cout << "По какой формуле проводить вычисления:" << endl << endl;

                cout << "1) По стороне и высоте" << endl;
                cout << "2) По сторонам и углу между ними" << endl;
                cout << "3) По диагоналям и углу между ними" << endl << endl;

                string selectStr;
                getline(cin, selectStr);

                int select = atoi(selectStr.c_str());

                switch (select) {

                case 1:
                    InitSideHeight();
                    isGo = false;
                    break;

                case 2:
                    InitSidesCorner();
                    isGo = false;
                    break;

                case 3:
                    InitSidesDiagonals();
                    isGo = false;
                    break;

                default:
                    SetConsoleTextAttribute(handleConsole, Red);
                    cout << "\nНекорректные данные!" << endl;
                    SetConsoleTextAttribute(handleConsole, White);
                    break;
                }
            }
        }
};

int main()
{
    handleConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    setlocale(LC_ALL, "Russian");

    cout << "Тема 1. Линейные вычислительные  процессы" << endl;
    cout << "Ларионов Никита Юрьевич. гр. 110з" << endl;

    bool isGo = true;

    while (isGo)
    {
        cout << "\nВведите номер задачи" << endl;
        cout << "6) Вычислить объём полого цилиндра" << endl;
        cout << "16) Вычислить площадь параллелограмма" << endl;
        cout << "Для выхода введите \"0\": ";

        string selectStr;
        getline(cin, selectStr);

        int select = atoi(selectStr.c_str());

        switch (select) {

        case 6:
            Task6 task6 = *new Task6();
            task6.Init();
            break;

        case 16:
            Task16 task16 = *new Task16();
            task16.Init();
            break;
     
        case 0:
            isGo = false;
            break;

        default:
            SetConsoleTextAttribute(handleConsole, Red);
            cout << "\nНекорректные данные!" << endl;
            SetConsoleTextAttribute(handleConsole, White);
            break;

        }
    }
}

