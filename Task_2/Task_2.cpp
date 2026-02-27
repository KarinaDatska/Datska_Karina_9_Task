#include <iostream>
#include <iomanip>

using namespace std;

const int N = 7;

double calculateSum(const double arr[]) {
    double s = 0;
    for (int i = 0; i < N; i++) s += arr[i];
    return s;
}

double calculateSumProd(const double x[], const double y[]) {
    double s = 0;
    for (int i = 0; i < N; i++) s += x[i] * y[i];
    return s;
}

double calculateProdInv(const double x[]) {
    double p = 1;
    for (int i = 0; i < N; i++) p *= (1.0 / x[i]);
    return p;
}

double calculateProdRatio(const double x[], const double y[]) {
    double p = 1;
    for (int i = 0; i < N; i++) p *= (x[i] / y[i]);
    return p;
}

int main() {
  
    double Xi[N] = { 1.1, 2.3, 4.5, 2.0, 4.2, 3.1, 1.8 };
    double Yi[N] = { -2.1, 3.0, 4.1, 2.5, 4.7, 6.8, 7.3 };
    double c = 5.0;

    double X_sum = calculateSum(Xi);          
    double Y_sum = calculateSum(Yi);          
    double a = calculateSumProd(Xi, Yi);     
    double b = calculateProdInv(Xi);          
    double d = calculateProdRatio(Xi, Yi);    
    
    double W = (a * X_sum + d * Y_sum) / (b * X_sum + c * Y_sum);

    cout << fixed << setprecision(4);
    cout << "\n------------------Result------------------\n" << endl;
    cout << "\tX = " << X_sum << ",\tY = " << Y_sum << endl;
    cout << "\ta = " << a << ",\tb = " << b << ",\n\td = " << d << endl;
    cout << "\n------------------------------------------\n" << endl;
    cout << "\t\tW = " << W << "\n\n" << endl;

    return 0;
}