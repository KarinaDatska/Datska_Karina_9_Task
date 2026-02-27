#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <future>
#include <windows.h>

using namespace std;
using namespace chrono;

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

void countingSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[minIndex])
                minIndex = j;
        swap(arr[i], arr[minIndex]);
    }
}

void quickSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void copyArray(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++)
        dest[i] = source[i];
}

void generateArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 10000;
}

void printArray(int arr[], int n) {
    int limit = (n > 20) ? 20 : n;
    for (int i = 0; i < limit; i++)
        cout << arr[i] << " ";
    if (n > 20) cout << "...";
    cout << endl;
}

int binarySearch(int arr[], int n, int key) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (arr[mid] == key)
            return mid;

        if (arr[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int main() {

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    srand(time(0));

    int sizes[] = { 8, 80, 1200, 4000, 25000, 100000 };
    int testCount = 6;

    for (int t = 0; t < testCount; t++) {

        int n = sizes[t];

        cout << "Початковий масив для N = " << n << ":\n";

        int* original = new int[n];
        generateArray(original, n);
        printArray(original, n);

        cout << "\nВведіть число для пошуку: ";
        int value;
        cin >> value;

        cout << "\n\tЧас виконання (мкс):\n";

        int* arr1 = new int[n];
        int* arr2 = new int[n];
        int* arr3 = new int[n];

        copyArray(original, arr1, n);
        auto start = high_resolution_clock::now();
        bubbleSort(arr1, n);
        auto end = high_resolution_clock::now();
        long long bubbleSync = duration_cast<microseconds>(end - start).count();

        copyArray(original, arr2, n);
        start = high_resolution_clock::now();
        countingSort(arr2, n);
        end = high_resolution_clock::now();
        long long selectionSync = duration_cast<microseconds>(end - start).count();

        copyArray(original, arr3, n);
        start = high_resolution_clock::now();
        quickSort(arr3, n);
        end = high_resolution_clock::now();
        long long insertionSync = duration_cast<microseconds>(end - start).count();

        cout << "\tBubble Sync: " << bubbleSync << endl;
        cout << "\tSelection Sync: " << selectionSync << endl;
        cout << "\tInsertion Sync: " << insertionSync << endl;

        cout << "\nРезультати бінарного пошуку:\n";

        int index1 = binarySearch(arr1, n, value);
        int index2 = binarySearch(arr2, n, value);
        int index3 = binarySearch(arr3, n, value);

        if (index1 != -1)
            cout << "\n\tBubble: знайдено за індексом " << index1 << endl;
        else
            cout << "\tBubble: не знайдено\n";

        if (index2 != -1)
            cout << "\tSelection: знайдено за індексом " << index2 << endl;
        else
            cout << "\tSelection: не знайдено\n";

        if (index3 != -1)
            cout << "\tInsertion: знайдено на за індексом " << index3 << endl;
        else
            cout << "\tInsertion: не знайдено\n";

        int* a1 = new int[n];
        int* a2 = new int[n];
        int* a3 = new int[n];

        copyArray(original, a1, n);
        copyArray(original, a2, n);
        copyArray(original, a3, n);
        auto asyncStart = high_resolution_clock::now();

        auto f1 = async(launch::async, bubbleSort, a1, n);
        auto f2 = async(launch::async, countingSort, a2, n);
        auto f3 = async(launch::async, quickSort, a3, n);

        f1.get();
        f2.get();
        f3.get();

        auto asyncEnd = high_resolution_clock::now();
        long long asyncTotal =
            duration_cast<microseconds>(asyncEnd - asyncStart).count();

        cout << "\nAsync (усі паралельно): " << asyncTotal << endl;
        cout << "\n----------------------------------------------------------\n";

        delete[] original;
        delete[] arr1;
        delete[] arr2;
        delete[] arr3;
        delete[] a1;
        delete[] a2;
        delete[] a3;
    }
    return 0;
}