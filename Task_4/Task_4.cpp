#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>

using namespace std;

bool isPalindrome(string word) {
    size_t left = 0;
    size_t right = word.length() - 1;

    while (left < right) {
        if (tolower((unsigned char)word[left]) != tolower((unsigned char)word[right]))
            return false;
        left++;
        right--;
    }
    return true;
}


int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    string line;

    while (getline(inputFile, line)) {
        stringstream ss(line);
        string word;
        bool found = false;

        while (ss >> word) {
            string clean = "";

            for (char c : word) {
                if (!ispunct((unsigned char)c) && !isspace((unsigned char)c)) {
                    clean += c;
                }
            }

            if (clean.length() < 2) continue;

            if (isPalindrome(clean)) {
                if (!found) {
                    outputFile << "Речення: " << line << endl;
                    found = true;
                }

                outputFile << "Паліндром: " << clean << endl;
            }
        }

        if (found) {
            outputFile << endl;
        }
    }

    inputFile.close();
    outputFile.close();

    return 0;
}