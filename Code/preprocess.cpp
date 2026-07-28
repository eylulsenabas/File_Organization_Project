#include "preprocess.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

using namespace std;

void cleanAndNormalizeData() {
    ifstream inFile("../RawData/passwords.txt");
    ofstream outFile("../Processed/cleaned_passwords.txt");

    if (!inFile.is_open() || !outFile.is_open()) {
        cerr << "[ERROR] Preprocess: Files could not be opened!\n";
        return;
    }

    unordered_set<string> seenPasswords;
    string password;
    cout << "[INFO] Preprocess: Cleaning data...\n";

    while (getline(inFile, password)) {
        if (password.length() > 0 && password[password.length() - 1] == '\r') {
            password.pop_back(); 
        }

        // Skip empty lines
        if (password.length() == 0) {
            continue;
        }

        // Skip duplicates (Adds if not in Set, returns false if already exists)
        bool isAdded = seenPasswords.insert(password).second;
        if (isAdded == false) {
            continue; 
        }

        // Write the clean password
        outFile << password << "\n";
    }

    inFile.close();
    outFile.close();
    cout << "[SUCCESS] Preprocess: Processed data is ready.\n";
}