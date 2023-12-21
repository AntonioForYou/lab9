#include <iostream>
#include <vector>
#include <cmath>
#include "Matrix.h"
#include <string>
// Внесение изсменений. master
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    
    size_t program;

    cout << "Метод гаусса: | 1 |, метод прогонки: | 2 |" << endl;
    
    do
    {
        cout << "Какую программу запустить: ";
        cin >> program;
    } while ((program != 1) && (program != 2));


    switch (program)
    {
        case 1:
        {
            Matrix a("Data_1.txt");

            a.display();

            a.GaussMethod();

            break;
        }
        

        case 2:
        {
            Matrix a("Data_2.txt");

            a.display();

            a.SweepMethod();

            break;
        }

    }
    

    return 0;
}
