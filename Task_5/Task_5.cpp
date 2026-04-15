#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

struct Bank {
    string name;
    double depositRate;
    double creditRate;
    int clientsCount;
    string country;
};

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    const int MAX_BANKS = 12;

    Bank banks[MAX_BANKS] = {
        {"PrivatBank", 12.5, 32.0, 1000000, "Ukraine"},
        {"Oschadbank", 11.0, 28.5, 800000, "Ukraine"},
        {"Raiffeisen", 13.2, 30.0, 500000, "Austria"},
        {"Monobank", 14.0, 29.5, 1200000, "Ukraine"},
        {"Ukreximbank", 10.5, 27.0, 300000, "Ukraine"},
        {"CreditAgricole", 13.8, 31.0, 450000, "France"},
        {"PiraeusBank", 12.0, 26.5, 600000, "Greece"}
    };

}