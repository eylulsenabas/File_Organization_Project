#include "utils.h"
#include <fstream>
#include <iostream>
#include <openssl/evp.h>
#include <vector>
#include <cstdlib> 
#include <ctime> 
#include <windows.h>
#include <psapi.h>

using namespace std;

long long getFileSize(const string& filepath) {
    ifstream file(filepath, ios::binary | ios::ate);
    if (!file.is_open()) return -1;
    long long size = file.tellg();
    file.close();
    return size;
}

string calculateMD5(const string& input) {
    unsigned char result[EVP_MAX_MD_SIZE]; 
    unsigned int length = 0;
    EVP_MD_CTX* context = EVP_MD_CTX_new();
    EVP_DigestInit_ex(context, EVP_md5(), nullptr);
    EVP_DigestUpdate(context, input.c_str(), input.length());
    EVP_DigestFinal_ex(context, result, &length);
    EVP_MD_CTX_free(context);

    string hashResult = "";
    char hexBuffer[3]; 
    for(unsigned int i = 0; i < length; i++) {
        sprintf(hexBuffer, "%02x", result[i]); 
        hashResult += hexBuffer;
    }
    return hashResult;
}

// Selects 'count' random passwords
vector<string> getRandomPasswords(int count) {
    vector<string> allPasswords;
    ifstream inFile("../Processed/cleaned_passwords.txt");
    string line;
    
    // Load all passwords temporarily into RAM
    while(getline(inFile, line)) {
        allPasswords.push_back(line);
    }
    inFile.close();

    vector<string> selected;
    srand(time(0)); 
    
    for(int i = 0; i < count; i++) {
        int randomIndex = rand() % allPasswords.size();
        selected.push_back(allPasswords[randomIndex]);
    }
    return selected;
}

// Returns the current RAM usage in MB
double getMemoryUsageMB() {
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        return (double)pmc.WorkingSetSize / (1024.0 * 1024.0);
    }
    return 0.0;
}