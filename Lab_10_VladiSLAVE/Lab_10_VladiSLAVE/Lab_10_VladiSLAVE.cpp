#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include<fstream>
#include <vector>

using namespace std;

const double eps = 0.00001;
const double h = 0.01;
const int n = (int)(5 * M_PI / h);

double f(double x, double y, double z)
{
    return z;
}

double g(double x, double y, double z)
{
    return -100 * y;
}

vector<double> rungeKutta(double alpha)
{
    vector<double> y(n + 1);
    y[0] = 0;
    double k1, k2, k3, k4;
    double l1, l2, l3, l4;
    double z = alpha;
    for (int i = 1; i <= n; i++) {
        k1 = h * f(i * h, y[i - 1], z);
        l1 = h * g(i * h, y[i - 1], z);
        k2 = h * f(i * h + h / 2.0, y[i - 1] + k1 / 2.0, z + l1 / 2.0);
        l2 = h * g(i * h + h / 2.0, y[i - 1] + k1 / 2.0, z + l1 / 2.0);
        k3 = h * f(i * h + h / 2.0, y[i - 1] + k2 / 2.0, z + l2 / 2.0);
        l3 = h * g(i * h + h / 2.0, y[i - 1] + k2 / 2.0, z + l2 / 2.0);
        k4 = h * f(i * h + h, y[i - 1] + k3, z + l3);
        l4 = h * g(i * h + h, y[i - 1] + k3, z + l3);
        y[i] = y[i - 1] + (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0;
        z += (l1 + 2.0 * l2 + 2.0 * l3 + l4) / 6.0;
    }
    return y;
}

double F(double alpha, double y1) {
    vector<double> y = rungeKutta(alpha);
    return y[n] - (y1);
}

int main() {
    setlocale(LC_ALL, "Russian");
    double a = -1000;
    double b = 1000;
    double y1 = 1;
    vector<double> angle;
    ofstream fout("Angle.txt");

    while (abs(F((a + b) / 2, y1)) > eps)
    {
        double c = (a + b) / 2;
        if (F(a, y1) * F(c, y1) < 0)
            b = c;
        else
            a = c;
        angle.push_back((a + b) / 2);
        fout << (a + b) / 2 << endl;
    }

    fout.close();

    vector<double> y = rungeKutta(angle.back());
    fout.open("Y.txt");

    for (auto iter : y)
    {
        fout << iter << endl;
    }

    fout.close();

    fout.open("X.txt");

    for (int i = 0; i <= n; i++)
        fout << i * h << endl;

    fout.close();

    cout << "Y(" << 1 << "): " << y.back() << endl;
    cout << "Разница между полученным значением и начальынм значением: " << F(angle.back(), y1) << endl;
    cout << "Alpha: " << angle.back() << endl;


    return 0;
}