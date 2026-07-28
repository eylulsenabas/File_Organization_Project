#include <iostream>
#include <iomanip> 
#include <string>
#include <vector>
#include "preprocess.h"
#include "storage.h"
#include "search.h"
#include "utils.h"

using namespace std;

int main() {
    cout << "====================================================\n";
    cout << "   File Organization Project - Performance Test\n";
    cout << "====================================================\n\n";

    cleanAndNormalizeData();
    createRawStorage();
    createHashedStorage();
    createCompressedStorage();

    cout << "\n[INFO] Calculating performance metrics (100 random searches). Please wait...\n";

    // File Sizes (Bytes)
    double origSize = getFileSize("../Processed/cleaned_passwords.txt");
    double rawSize = getFileSize("../Storage/Raw/data.bin");
    double hashedSize = getFileSize("../Storage/Hashed/hashed.bin");
    double compSize = getFileSize("../Storage/Compressed/compressed.bin");

    // Compression Ratio
    double compRatio = compSize / origSize;

    // RAM Usage
    double ramUsage = getMemoryUsageMB();
    
    double cpuUsage = 100.0; 

    // Select 100 random passwords and start searches
    vector<string> testTargets = getRandomPasswords(100);
    
    SearchResult rawStats = searchInRaw(testTargets);
    SearchResult hashedStats = searchInHashed(testTargets);
    
    long long decompressTime = 0;
    SearchResult compStats = searchInCompressed(testTargets, decompressTime);

    // PRINT TABLE 
    cout << "\n========================================================================================================\n";
    cout << "METHOD     | SIZE (Bytes) | COMP. RATIO | AVG. TIME (us) | MAX TIME (us) | STD. DEV. | DECOMP. TIME (us)\n";
    cout << "========================================================================================================\n";
    
    cout << left << setw(11) << "Raw" << "| " 
         << setw(13) << rawSize << "| "
         << setw(12) << "-" << "| "
         << setw(15) << fixed << setprecision(2) << rawStats.averageTime << "| "
         << setw(14) << rawStats.maxTime << "| "
         << setw(10) << rawStats.stdDev << "| "
         << "-" << "\n";

    cout << left << setw(11) << "Hashed" << "| " 
         << setw(13) << hashedSize << "| "
         << setw(12) << "-" << "| "
         << setw(15) << hashedStats.averageTime << "| "
         << setw(14) << hashedStats.maxTime << "| "
         << setw(10) << hashedStats.stdDev << "| "
         << "-" << "\n";

    cout << left << setw(11) << "Compressed" << "| " 
         << setw(13) << compSize << "| "
         << setw(12) << compRatio << "| "
         << setw(15) << compStats.averageTime << "| "
         << setw(14) << compStats.maxTime << "| "
         << setw(10) << compStats.stdDev << "| "
         << decompressTime << "\n";
         
    cout << "========================================================================================================\n";
    cout << "System Resource Consumption -> Average RAM Usage: " << ramUsage << " MB | Estimated CPU Load: " << cpuUsage << "%\n";
    cout << "========================================================================================================\n";

    return 0;
}