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

string GetLine() {
    string line;
    getline(cin, line);
    cin.clear();
    return line;
}

class MyInput {

    public: 

        bool isDouble(string str) {
            return str.find_first_not_of("-1234567890,") == string::npos;
        }

        double InputData(string text, int min, int max, int defaultValue = -1) {

            string xStr = "";
            double result = 0;
            bool isNumber = true;

            while (true) {

                SetConsoleTextAttribute(handleConsole, White);
                cout << text;

                xStr = GetLine();

                if (xStr == "" && defaultValue != -1)
                    return defaultValue;


                try {
                    result = stod(xStr.c_str());
                    isNumber = true;
                }
                catch (...) {
                    isNumber = false;
                }

                if (!(isNumber && isDouble(xStr))) {
                    SetConsoleTextAttribute(handleConsole, Red);
                    cout << endl << xStr + " - не число!" << endl << endl;
                }
                else if (result > max || result < min) {
                    SetConsoleTextAttribute(handleConsole, Red);
                    cout << endl << "Число должно лежать в промежутке [" << min << "; " << max << "]!" << endl << endl;
                }
                else
                    break;
            }

            return result;
        }

};

class MyRandom {
    
    public:
        static const int MIN_RANDOM = 2, MAX_RANDOM = 1000;

        bool isRandomData() {
            cout << "Сгенерировать данные случайным образом [y/n]?" << endl;

            string answer = GetLine();

            transform(answer.begin(), answer.end(), answer.begin(), tolower);

            return answer == "y" || answer == "";
        }

        double GetRandom(int min, int max) {

            random_device random_device; // Источник энтропии.
            mt19937 generator(random_device()); // Генератор случайных чисел.

            // (Здесь берется одно инициализирующее значение, можно брать больше)
            uniform_int_distribution<> distribution(min, max); // Равномерное распределение [min, max]

            return distribution(generator);

            //return rand() % (max - min) - min;
            //return rand() % max + min;
        }


};

class Task6 {

    private:
        double printVolume(double h, double r1, double r2) {

            cout << "v = ПИ * h (r1^2 - r2^2)" << endl;
            cout << "v = " << PI << " * " << h << " * (" << fixed << r1 <<"^2 - " << fixed << r2 << "^2)" << endl;

            double square1 = r1 * r1;
            double square2 = r2 * r2;

            cout << "v = " << PI << " * " << h << " * (" << fixed << square1 << " - " << fixed << square2 << ")" << endl;

            double differenceSquare = square1 - square2;
            cout << "v = " << PI << " * " << fixed << h << " * " << fixed << differenceSquare << endl;

            double result = PI * h * differenceSquare;
            cout << "v = " << fixed << result << endl;
            return result;
        }


    public:
        const int MIN = MyRandom::MIN_RANDOM;
        const int MAX = MyRandom::MAX_RANDOM;

        void Init() {

            HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(handleConsole, White);

            cout << "\nВычислить v (объём) полого цилиндра\n";
            cout << "высотой h\n";
            cout << "внешним радиусом r1\n";
            cout << "внутренним радиусом r2\n\n";

            cout << "По формуле: v = ПИ * h (r1^2 - r2^2)\n\n";

            
            double r1, r2, h;

            MyRandom myRandom = *new MyRandom();
            
            if (myRandom.isRandomData()) {
                h =  myRandom.GetRandom(MIN, MAX);

                while (true) {
                    r2 = myRandom.GetRandom(MIN, MAX) - 1;
                    r1 = myRandom.GetRandom(r2, MAX);

                    if (r1 > r2)
                        break;
                }
            }
            else {
                MyInput myInput = *new MyInput();

                h = myInput.InputData("Введите высоту цилиндра: ", MIN, MAX);

                while (true) {
                    SetConsoleTextAttribute(handle, White);

                    r1 = myInput.InputData("Введите внешний радиус цилиндра: ", MIN, MAX);
                    r2 = myInput.InputData("Введите внутренний радиус цилиндра: ", MIN, MAX);

                    if (r1 <= r2) {
                        SetConsoleTextAttribute(handle, Red);
                        cout << endl << "Внешний радиус цилиндра должен быть больше внутреннего!" << endl;
                    }
                    else
                        break;
                }
              
            }

            SetConsoleTextAttribute(handleConsole, Yellow);
            cout << endl << "Полученные данные:" << endl;
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
        double degreeToRadian(double degree) {

            return (degree * PI) / 180;
        }

        double printSquare(double side, double height) {
            
            cout << "S = a * h" << endl;
            cout << "S = " << side << " * " << height << endl;
            
            double result = side * height;
            cout << "S = " << result << endl;

            return result;
        }

        double printSquareCorner(double side1, double side2, double corner) {

            cout << "S = a * b * sin(A)" << endl;
            cout << "S = " << fixed << side1 << " * " << fixed << side2 << " * sin(" << fixed << corner << ")" << endl;

            double sinCorner = sin(degreeToRadian(corner));

            cout << "S = " << fixed << side1 << " * " << fixed << side2 << " * " << fixed << sinCorner << endl;

            double result = side1 * side2 * sinCorner;

            cout << "S = " << fixed << result << endl;

            return result;
        }

        double printSquareDiagonals(double d1, double d2, double corner) {

            cout << "S = 0.5 * d1 * d2 * sin(A)" << endl;
            cout << "S = 0.5 * " << fixed << d1 << " * " << fixed << d2 << " * sin(" << fixed << corner << ")" << endl;

            double sinCorner = sin(degreeToRadian(corner));

            cout << "S = 0.5 * " << fixed << d1 << " * " << fixed << d2 << " * " << fixed << sinCorner << endl;

            double result = (d1 * d2 * sinCorner) / 2;

            cout << "S = " << fixed << result << endl;

            return result;
        }

    public:
        const int MIN = MyRandom::MIN_RANDOM;
        const int MAX = MyRandom::MAX_RANDOM;

        void InitSideHeight() {

            double side, height;

            MyRandom myRandom = *new MyRandom();

            if (myRandom.isRandomData()) {
                side = myRandom.GetRandom(MIN, MAX);
                height = myRandom.GetRandom(MIN, MAX);
            }
            else {
                MyInput myInput = *new MyInput();
                side = myInput.InputData("Введите сторону параллелограмма: ", MIN, MAX);
                height = myInput.InputData("Введите высоту параллелограмма: ", MIN, MAX);
            }

            SetConsoleTextAttribute(handleConsole, Yellow);
            cout << endl << "Полученные данные:" << endl;
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
                side1 = myRandom.GetRandom(MIN, MAX);
                side2 = myRandom.GetRandom(MIN, MAX);
                corner = myRandom.GetRandom(MIN, 89);
            }
            else {
                MyInput myInput = *new MyInput();
                side1 = myInput.InputData("Введите первую сторону параллелограмма (а): ", MIN, MAX);
                side2 = myInput.InputData("Введите вторую сторону параллелограмма (b): ", MIN, MAX);
                corner = myInput.InputData("Введите угол между сторонами а и b (A) [в градусах]: ", MIN, 90);
            }

            SetConsoleTextAttribute(handleConsole, Yellow);
            cout << endl << "Полученные данные:" << endl;
            cout << "Первая сторона параллелограмма (а): " << side1 << endl;
            cout << "Вторая сторона параллелограмма (b): " << side2 << endl;
            cout << "Угол между сторонами а и b (A) [в градусах]: " << corner << endl << endl;

            SetConsoleTextAttribute(handleConsole, Green);
            printSquareCorner(side1, side2, corner);

            SetConsoleTextAttribute(handleConsole, White);
        }

        void InitSidesDiagonals() {

            double d1, d2, corner;

            MyRandom myRandom = *new MyRandom();

            if (myRandom.isRandomData()) {
                d1 = myRandom.GetRandom(MIN, MAX);
                d2 = myRandom.GetRandom(MIN, MAX);
                corner = myRandom.GetRandom(MIN, 179);
            }
            else {
                MyInput myInput = *new MyInput();
                d1 = myInput.InputData("Введите первую диагональ параллелограмма (d1): ", MIN, MAX);
                d2 = myInput.InputData("Введите вторую дигональ параллелограмма (d2): ", MIN, MAX);
                corner = myInput.InputData("Введите угол между диагоналями d1 и d2 (A): ", MIN, 180);
            }

            SetConsoleTextAttribute(handleConsole, Yellow);
            cout << endl << "Полученные данные:" << endl;
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
            string select;

            while (isGo)
            {
                cout << "\nВычислить S (площадь) параллелограмма" << endl;
                cout << "По какой формуле проводить вычисления:" << endl << endl;

                cout << "1) По стороне и высоте" << endl;
                cout << "2) По сторонам и углу между ними" << endl;
                cout << "3) По диагоналям и углу между ними" << endl << endl;

                select = GetLine();

                if (select == "1") {
                    InitSideHeight();
                    isGo = false;
                }
                else if (select == "2") {
                    InitSidesCorner();
                    isGo = false;
                }
                else if (select == "3") {
                    InitSidesDiagonals();
                    isGo = false;
                }
                else {
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

    SetConsoleTextAttribute(handleConsole, White);

    cout << "Тема 1. Линейные вычислительные  процессы" << endl;
    cout << "Ларионов Никита Юрьевич. гр. 110з" << endl;

    bool isGo = true;
    string select;

    while (isGo)
    {

        cout << "\nВведите номер задачи" << endl;
        cout << "6) Вычислить v (объём) полого цилиндра" << endl;
        cout << "16) Вычислить площадь параллелограмма" << endl;
        cout << "Для выхода введите \"0\": ";

        select = GetLine();
      
        if (select == "6") {
            Task6 task6 = *new Task6();
            task6.Init();
        }
        else if (select == "16") {
            Task16 task16 = *new Task16();
            task16.Init();
        } 
        else if (select == "0") {
            isGo = false;
        }
        else {
            SetConsoleTextAttribute(handleConsole, Red);
            cout << "\nНекорректные данные!" << endl;
            SetConsoleTextAttribute(handleConsole, White);
        }

    }
}

