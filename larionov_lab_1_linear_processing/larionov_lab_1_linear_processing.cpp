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
                    cout << xStr + " - �� �����!";
                }
                else if(atof(xStr.c_str()) <= 0) {
                    SetConsoleTextAttribute(handleConsole, Red);
                    cout << "����� ������ ���� ������ ����!";
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
            cout << "������������� ������ ��������� ������� [y/n]?" << endl;

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

            cout << "v = �� * h (r1^2 - r2^2)" << endl;
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

            cout << "\n��������� v (�����) ������ ��������" << endl;
            cout << "������� h" << endl;
            cout << "������� �������� r1" << endl;
            cout << "���������� �������� r2" << endl << endl;

            cout << "�� �������: v = �� * h (r1^2 - r2^2)" << endl << endl;

            double r1, r2, h;

            MyRandom myRandom = *new MyRandom();
            
            if (myRandom.isRandomData()) {
                r2 = myRandom.GetRandom(myRandom.MIN_RANDOM, myRandom.MAX_RANDOM) - 1;
                r1 = myRandom.GetRandom(r2, myRandom.MAX_RANDOM);
                h =  myRandom.GetRandom(myRandom.MIN_RANDOM, myRandom.MAX_RANDOM);
            }
            else {
                MyInput myInput = *new MyInput();

                h = myInput.InputData("������� ������ ��������: ");

                while (true) {
                    SetConsoleTextAttribute(handle, 37);

                    r1 = myInput.InputData("������� ������� ������ ��������: ");
                    r2 = myInput.InputData("������� ���������� ������ ��������: ");

                    if (r1 <= r2) {
                        SetConsoleTextAttribute(handle, 4);
                        cout << "������� ������ �������� ������ ���� ������ �����������!";
                    }
                    else
                        break;
                }
              
            }

            SetConsoleTextAttribute(handleConsole, Yellow);
            cout << "���������� ������:" << endl;
            cout << "������ �������� (h): " << h << endl;
            cout << "������� ������ �������� (r1): " << r1 << endl;
            cout << "���������� ������ �������� (r2): " << r2 << endl << endl;


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
                side = myInput.InputData("������� ������� ���������������: ");
                height = myInput.InputData("������� ������ ���������������: ");
            }

            SetConsoleTextAttribute(handleConsole, Yellow);
            cout << "���������� ������:" << endl;
            cout << "������� ��������������� (a): " << side << endl;
            cout << "������ ���������������: (h): " << height << endl << endl;

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
                side1 = myInput.InputData("������� ������ ������� ��������������� (�): ");
                side2 = myInput.InputData("������� ������ ������� ��������������� (b): ");
                corner = myInput.InputData("������� ���� ����� ��������� � � b (A): ");
            }

            SetConsoleTextAttribute(handleConsole, Yellow);
            cout << "���������� ������:" << endl;
            cout << "������ ������� ��������������� (�): " << side1 << endl;
            cout << "������ ������� ��������������� (b): " << side2 << endl;
            cout << "���� ����� ��������� � � b (A): " << corner << endl << endl;

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
                d1 = myInput.InputData("������� ������ ��������� ��������������� (d1): ");
                d2 = myInput.InputData("������� ������ �������� ��������������� (d2): ");
                corner = myInput.InputData("������� ���� ����� ����������� d1 � d2 (A): ");
            }

            SetConsoleTextAttribute(handleConsole, Yellow);
            cout << "���������� ������:" << endl;
            cout << "������ ��������� ��������������� (d1): " << d1 << endl;
            cout << "������ ��������� ��������������� (d2): " << d2 << endl;
            cout << "���� ����� ����������� d1 � d2 (A): " << corner << endl << endl;

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
                cout << "\n��������� S (�������) ���������������" << endl;
                cout << "�� ����� ������� ��������� ����������:" << endl << endl;

                cout << "1) �� ������� � ������" << endl;
                cout << "2) �� �������� � ���� ����� ����" << endl;
                cout << "3) �� ���������� � ���� ����� ����" << endl << endl;

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
                    cout << "\n������������ ������!" << endl;
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

    cout << "���� 1. �������� ��������������  ��������" << endl;
    cout << "�������� ������ �������. ��. 110�" << endl;

    bool isGo = true;

    while (isGo)
    {
        cout << "\n������� ����� ������" << endl;
        cout << "6) ��������� ����� ������ ��������" << endl;
        cout << "16) ��������� ������� ���������������" << endl;
        cout << "��� ������ ������� \"0\": ";

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
            cout << "\n������������ ������!" << endl;
            SetConsoleTextAttribute(handleConsole, White);
            break;

        }
    }
}

