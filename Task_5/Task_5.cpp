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

    int realBanks = 7;

    string filename = "banks.txt";

    ofstream outFile(filename);
    if (!outFile) {
        cout << "Error opening file for writing!" << endl;
        return 1;
    }

    for (int i = 0; i < realBanks; i++) {
        outFile << banks[i].name << " "
            << banks[i].depositRate << " "
            << banks[i].creditRate << " "
            << banks[i].clientsCount << " "
            << banks[i].country << endl;
    }
    outFile.close();

    Bank loadedBanks[MAX_BANKS];
    int count = 0;

    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error opening file for reading!" << endl;
        return 1;
    }

    while (count < MAX_BANKS &&
        inFile >> loadedBanks[count].name
        >> loadedBanks[count].depositRate
        >> loadedBanks[count].creditRate
        >> loadedBanks[count].clientsCount
        >> loadedBanks[count].country) {
        count++;
    }

    inFile.close();

    int bestDepIdx = 0;
    int bestCredIdx = 0;

    for (int i = 1; i < count; i++) {
        if (loadedBanks[i].depositRate > loadedBanks[bestDepIdx].depositRate) {
            bestDepIdx = i;
        }

        if (loadedBanks[i].creditRate < loadedBanks[bestCredIdx].creditRate) {
            bestCredIdx = i;
        }
    }
    cout << "\n\t----- Результати аналізу -----\n" << endl;
    cout << "\tНайкращий депозит: " << loadedBanks[bestDepIdx].name
        << " (" << loadedBanks[bestDepIdx].depositRate << "%)" << endl;

    cout << "\tНайкращий кредит: " << loadedBanks[bestCredIdx].name
        << " (" << loadedBanks[bestCredIdx].creditRate << "%)\n" << endl;

    return 0;
}