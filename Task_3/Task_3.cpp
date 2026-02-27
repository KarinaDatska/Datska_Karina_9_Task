#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip> 
#include <windows.h>

using namespace std;

int** createMatrix(int n) {
    int** a = new int* [n];
    for (int i = 0; i < n; i++)
        a[i] = new int[n];
    return a;
}

void fillMatrix(int** a, int n, int V) {
    int minVal = -10 - V;
    int maxVal = 10 + V;
    int range = maxVal - minVal + 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = rand() % range + minVal;
}

void printMatrix(int** a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << setw(5) << a[i][j]; 
        cout << endl;
    }
}

void sector4_backslash(int** a, int n, int k) {
    cout << "\n--- Аналіз сектора 4\\ ---\n";
    if (k == 0) {
        cout << "Помилка: ділення на 0!\n";
        return;
    }

    int count = 0;
    bool found = false;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i >= j && i + j >= n - 1) {
                count++;
                if (!found && a[i][j] % k == 0) {
                    cout << "Перший елемент, що ділиться на " << k << ": " << a[i][j]
                        << " (порядковий номер у секторі: " << count << ")\n";
                    found = true;
                }
            }
        }
    }
    if (!found) cout << "Елементів, що діляться на " << k << ", не знайдено.\n";
}


void sector7_processing(int** a, int n) {
    cout << "\n--- Обробка сектора 7 ---\n";
    int maxDiag = a[0][0];
    for (int i = 1; i < n; i++) {
        if (a[i][i] > maxDiag) maxDiag = a[i][i];
    }
    cout << "Максимум головної діагоналі: " << maxDiag << endl;

    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i < j && i + j < n - 1) {
                count++;
                a[i][j] = maxDiag;
            }
        }
    }
    cout << "Кількість змінених елементів у секторі 7: " << count << endl;
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    srand(time(0));

    int n, V, k;
    cout << "Введіть n (розмір n x n): "; cin >> n;
    cout << "Введіть номер варіанта V: "; cin >> V;
    cout << "Введіть число k: "; cin >> k;

    if (n <= 0) {
        cout << "Розмір має бути додатним!";
        return 0;
    }

    int** matrix = createMatrix(n);
    fillMatrix(matrix, n, V);

    cout << "\nПочаткова матриця:\n";
    printMatrix(matrix, n);

    sector4_backslash(matrix, n, k);
    sector7_processing(matrix, n);

    cout << "\nМатриця після змін:\n";
    printMatrix(matrix, n);

    for (int i = 0; i < n; i++) delete[] matrix[i];
    delete[] matrix;

    return 0;
}