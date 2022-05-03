#include <iostream>
#include <Windows.h>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <random>
#include <algorithm>
#include <iomanip>
#include <regex>


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

string RoundStr(float var, int after = 2) {

    string s = to_string(var);
    int size = s.size();

    string result = "";
    bool isAfter = false;
    int afterCount = 0;

    for (int i = 0; i < size; ++i) {

        if (afterCount == after)
            break;

        if (isAfter)
            ++afterCount;

        if (!isAfter && s[i] == ',')
            isAfter = true;

        result += s[i];

    }

    return result;
}

float Round(float var)
{
    // 37.66666 * 100 = 3766.66
    // 3766.66 + .5 = 3767.16 для значения округления

    // затем вводим тип int в значение 3767
    // затем делим на 100, поэтому значение преобразуется в 37,67

    float value = (int)(var * 100 + .5);
    return stod(RoundStr((float)value / 100));

}

class MyInput {

    public: 

        bool isDouble(string str) {
            return regex_match(str, regex("^[-]?[0-9]*?,?[0-9]*"));
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

            transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

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
        const int MIN = MyRandom::MIN_RANDOM;
        const int MAX = 100;

        double printVolume(double h, double r1, double r2) {

            double square1 = Round(r1 * r1);
            double square2 = Round(r2 * r2);

            double differenceSquare = Round(square1 - square2);
            double result = Round(PI * h * differenceSquare);

            string strH = RoundStr(h);

            cout << "v = ПИ * h (r1^2 - r2^2)" << endl;
            cout << "v = " << PI << " * " << strH << " * (" << fixed << RoundStr(r1) <<"^2 - " << fixed << RoundStr(r2) << "^2)" << endl;

            cout << "v = " << PI << " * " << strH << " * (" << fixed << RoundStr(square1) << " - " << fixed << RoundStr(square2) << ")" << endl;
            cout << "v = " << PI << " * " << fixed << strH << " * " << fixed << RoundStr(differenceSquare) << endl;

            cout << "v = " << fixed << RoundStr(result) << endl;
            return result;
        }


    public:
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

            h = Round(h);
            r1 = Round(r1);
            r2 = Round(r2);

            SetConsoleTextAttribute(handleConsole, Yellow);
            cout << endl << "Полученные данные:" << endl;
            cout << "Высота цилиндра (h): " << RoundStr(h) << endl;
            cout << "Внешний радиус цилиндра (r1): " << RoundStr(r1) << endl;
            cout << "Внутренний радиус цилиндра (r2): " << RoundStr(r2) << endl << endl;


            SetConsoleTextAttribute(handleConsole, Green);
            printVolume(h, r1, r2);

            SetConsoleTextAttribute(handleConsole, White);

        }  

};

class Task16 {

    private:
        const int MIN = MyRandom::MIN_RANDOM;
        const int MAX = MyRandom::MAX_RANDOM;

        double degreeToRadian(double degree) {
            return (degree * PI) / 180;
        }

        double radianToDegree(double radian) {
            return (radian * 180) / PI;
        }

        double printSquare(double side, double height) {
            
            cout << "S = a * h" << endl;
            cout << "S = " << RoundStr(side) << " * " << RoundStr(height) << endl;
            
            double result = Round(side * height);
            cout << "S = " << RoundStr(result) << endl;

            return result;
        }

        double printSquareCorner(double side1, double side2, double corner) {

            string strSide1 = RoundStr(side1);
            string strSide2 = RoundStr(side2);

            cout << "S = a * b * sin(A)" << endl;
            cout << "S = " << fixed << strSide1 << " * " << fixed << strSide2 << " * sin(" << fixed << RoundStr(corner) << ")" << endl;

            double sinCorner = sin(degreeToRadian(corner));

            cout << "S = " << fixed << strSide1 << " * " << fixed << strSide2 << " * " << fixed << RoundStr(sinCorner) << endl;

            double result = Round(side1 * side2 * sinCorner);

            cout << "S = " << fixed << RoundStr(result) << endl;

            return result;
        }

        double printSquareDiagonals(double d1, double d2, double corner) {

            double sinCorner = sin(degreeToRadian(corner));
            double result = Round((d1 * d2 * sinCorner) / 2);

            string strD1 = RoundStr(d1);
            string strD2 = RoundStr(d2);

            cout << "S = 0.5 * d1 * d2 * sin(A)" << endl;
            cout << "S = 0.5 * " << fixed << strD1 << " * " << fixed << strD2 << " * sin(" << fixed << RoundStr(corner) << ")" << endl;

            cout << "S = 0.5 * " << fixed << strD1 << " * " << fixed << strD2 << " * " << fixed << RoundStr(sinCorner) << endl;
            cout << "S = " << fixed << RoundStr(result) << endl;

            return result;
        }

    public:

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

            side = Round(side);
            height = Round(height);

            SetConsoleTextAttribute(handleConsole, Yellow);
            cout << endl << "Полученные данные:" << endl;
            cout << "Сторона параллелограмма (a): " << RoundStr(side) << endl;
            cout << "Высота параллелограмма: (h): " << RoundStr(height) << endl << endl;

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

            side1 = Round(side1);
            side2 = Round(side2);
            corner = Round(corner);

            SetConsoleTextAttribute(handleConsole, Yellow);
            cout << endl << "Полученные данные:" << endl;
            cout << "Первая сторона параллелограмма (а): " << RoundStr(side1) << endl;
            cout << "Вторая сторона параллелограмма (b): " << RoundStr(side2) << endl;
            cout << "Угол между сторонами а и b (A) [в градусах]: " << RoundStr(corner) << endl << endl;

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

            d1 = Round(d1);
            d2 = Round(d2);
            corner = Round(corner);

            SetConsoleTextAttribute(handleConsole, Yellow);
            cout << endl << "Полученные данные:" << endl;
            cout << "Первая диагональ параллелограмма (d1): " << RoundStr(d1) << endl;
            cout << "Вторая диагональ параллелограмма (d2): " << RoundStr(d2) << endl;
            cout << "Угол между диагоналями d1 и d2 (A): " << RoundStr(corner) << endl << endl;

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

