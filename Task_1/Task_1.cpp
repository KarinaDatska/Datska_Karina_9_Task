#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <future>
#include <windows.h>

using namespace std;
using namespace chrono;

void generateArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 1000;
}

void printArray(int arr[], int n) {
    int limit = (n > 20) ? 20 : n;
    for (int i = 0; i < limit; i++)
        cout << arr[i] << " ";
    if (n > 20) cout << "...";
    cout << endl;
}

void copyArray(int src[], int dest[], int n) {
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

void countingSort(int arr[], int n) {
    int maxVal = arr[0];

    for (int i = 1; i < n; i++)
        if (arr[i] > maxVal)
            maxVal = arr[i];

    int* count = new int[maxVal + 1]();

    for (int i = 0; i < n; i++)
        count[arr[i]]++;

    int index = 0;
    for (int i = 0; i <= maxVal; i++) {
        while (count[i] > 0) {
            arr[index++] = i;
            count[i]--;
        }
    }

    delete[] count;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int binarySearch(int arr[], int n, int key) {
    int left = 0, right = n - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (arr[mid] == key) return mid;
        if (arr[mid] < key) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int main() {
    SetConsoleOutputCP(65001);
    srand(time(0));

    int sizes[] = { 8, 80, 1200, 4000, 25000, 100000 };

    for (int s = 0; s < 6; s++) {

        int n = sizes[s];
        cout << "\n----- N = " << n << " -----\n";

        int* original = new int[n];
        generateArray(original, n);
        printArray(original, n);

        int* a = new int[n];
        int* b = new int[n];
        int* c = new int[n];

        copyArray(original, a, n);
        auto start = high_resolution_clock::now();
        bubbleSort(a, n);
        auto end = high_resolution_clock::now();
        auto tBubble = duration_cast<microseconds>(end - start).count();

        copyArray(original, b, n);
        start = high_resolution_clock::now();
        countingSort(b, n);
        end = high_resolution_clock::now();
        auto tCount = duration_cast<microseconds>(end - start).count();

        copyArray(original, c, n);
        start = high_resolution_clock::now();
        quickSort(c, 0, n - 1);
        end = high_resolution_clock::now();
        auto tQuick = duration_cast<microseconds>(end - start).count();

        cout << "\nЧас (мкс):\n";
        cout << "Bubble: " << tBubble << endl;
        cout << "Counting: " << tCount << endl;
        cout << "Quick: " << tQuick << endl;

        int value;
        cout << "\nВведи число для пошуку: ";
        cin >> value;

        int index = binarySearch(c, n, value);

        if (index != -1)
            cout << "Знайдено (QuickSort) індекс: " << index << endl;
        else
            cout << "Не знайдено\n";

        int* a1 = new int[n];
        int* a2 = new int[n];
        int* a3 = new int[n];

        copyArray(original, a1, n);
        copyArray(original, a2, n);
        copyArray(original, a3, n);

        auto asyncStart = high_resolution_clock::now();

        auto f1 = async(launch::async, bubbleSort, a1, n);
        auto f2 = async(launch::async, countingSort, a2, n);
        auto f3 = async(launch::async, quickSort, a3, 0, n - 1);

        f1.get();
        f2.get();
        f3.get();

        auto asyncEnd = high_resolution_clock::now();
        auto tAsync = duration_cast<microseconds>(asyncEnd - asyncStart).count();

        cout << "\nАсинхронний час (мкс): " << tAsync << endl;

        delete[] original;
        delete[] a;
        delete[] b;
        delete[] c;
        delete[] a1;
        delete[] a2;
        delete[] a3;
    }

    return 0;
}