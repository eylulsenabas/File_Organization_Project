#include "storage.h"
#include "utils.h"
#include "compression.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const string PROCESSED_FILE = "../Processed/cleaned_passwords.txt";

void createRawStorage() {
    const string RAW_STORAGE_FILE = "../Storage/Raw/data.bin"; 
    
    ifstream inFile(PROCESSED_FILE);
    ofstream outFile(RAW_STORAGE_FILE);

    if (!inFile.is_open() || !outFile.is_open()) return;

    string line;
    cout << "[INFO] Storage: Creating Raw data file...\n";
    
    while (getline(inFile, line)) {
        outFile << line << "\n";
    }

    inFile.close();
    outFile.close();
    cout << "[SUCCESS] Storage: Raw storage completed.\n";
}

void createHashedStorage() {
    const string HASHED_STORAGE_FILE = "../Storage/Hashed/hashed.bin";
    
    ifstream inFile(PROCESSED_FILE);
    ofstream outFile(HASHED_STORAGE_FILE);

    if (!inFile.is_open() || !outFile.is_open()) return;

    string line;
    cout << "[INFO] Storage: Creating Hashed data file...\n";
    
    while (getline(inFile, line)) {
        outFile << calculateMD5(line) << "\n";
    }

    inFile.close();
    outFile.close();
    cout << "[SUCCESS] Storage: Hashed storage completed.\n";
}

void createCompressedStorage() {
    cout << "[INFO] Storage: Creating Compressed data file...\n";
    
    string COMPRESSED_FILE = "../Storage/Compressed/compressed.bin";
    compressData(PROCESSED_FILE, COMPRESSED_FILE);

    cout << "[SUCCESS] Storage: Compressed storage completed.\n";
}
