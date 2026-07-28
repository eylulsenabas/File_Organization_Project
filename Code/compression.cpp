#include "compression.h"
#include <iostream>
#include <fstream>
#include <string>
#include <zlib.h> 

using namespace std;

void compressData(const string& inFilePath, const string& outFilePath) {
    ifstream inFile(inFilePath);
    if (!inFile.is_open()) {
        cerr << "[ERROR] Compression: Processed file to read could not be opened!\n";
        return;
    }

    gzFile outFile = gzopen(outFilePath.c_str(), "wb");
    if (outFile == nullptr) {
        cerr << "[ERROR] Compression: Compressed file could not be created!\n";
        inFile.close();
        return;
    }

    string line;
    while (getline(inFile, line)) {
        line += "\n"; 
        gzputs(outFile, line.c_str());
    }

    inFile.close();
    gzclose(outFile);
} 

void decompressData(const string& inFilePath, const string& outFilePath) {
    gzFile inFile = gzopen(inFilePath.c_str(), "rb");
    ofstream outFile(outFilePath);

    if (inFile == nullptr || !outFile.is_open()) {
        cerr << "[ERROR] Compression: Files could not be prepared for decompression!\n";
        return;
    }

    char buffer[1024]; 
    while (gzgets(inFile, buffer, sizeof(buffer)) != nullptr) {
        outFile << buffer;
    }

    gzclose(inFile);
    outFile.close();
}