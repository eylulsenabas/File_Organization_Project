#include "search.h"
#include "utils.h"
#include "compression.h"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cmath> 
#include <cstdio> 

using namespace std;
using namespace std::chrono;

// calculation function
SearchResult calculateStats(const vector<long long>& times) {
    SearchResult result = {0.0, 0, 0.0};
    if (times.empty()) return result;

    long long sum = 0;
    for (long long t : times) {
        sum += t;
        if (t > result.maxTime) result.maxTime = t;
    }
    
    result.averageTime = (double)sum / times.size();

    double varianceSum = 0;
    for (long long t : times) {
        varianceSum += pow(t - result.averageTime, 2);
    }
    result.stdDev = sqrt(varianceSum / times.size());

    return result;
}

SearchResult searchInRaw(const vector<string>& targets) {
    vector<long long> searchTimes;

    for (const string& target : targets) {
        auto start = high_resolution_clock::now();
        ifstream inFile("../Storage/Raw/data.bin");
        string line;
        while (getline(inFile, line)) {
            if (line == target) break;
        }
        inFile.close();
        auto stop = high_resolution_clock::now();
        searchTimes.push_back(duration_cast<microseconds>(stop - start).count());
    }
    return calculateStats(searchTimes);
}

SearchResult searchInHashed(const vector<string>& targets) {
    vector<long long> searchTimes;

    for (const string& target : targets) {
        auto start = high_resolution_clock::now();
        
        string targetHash = calculateMD5(target);
        ifstream inFile("../Storage/Hashed/hashed.bin");
        string line;
        while (getline(inFile, line)) {
            if (line == targetHash) break;
        }
        inFile.close();
        
        auto stop = high_resolution_clock::now();
        searchTimes.push_back(duration_cast<microseconds>(stop - start).count());
    }
    return calculateStats(searchTimes);
}

SearchResult searchInCompressed(const vector<string>& targets, long long& decompressTime) {
    string compFile = "../Storage/Compressed/compressed.bin";
    string tempFile = "../Storage/Compressed/temp_search.txt";

    // Measure Decompression Time
    auto decStart = high_resolution_clock::now();
    decompressData(compFile, tempFile);
    auto decStop = high_resolution_clock::now();
    decompressTime = duration_cast<microseconds>(decStop - decStart).count();

    vector<long long> searchTimes;

    for (const string& target : targets) {
        auto start = high_resolution_clock::now();
        
        ifstream inFile(tempFile);
        string line;
        while (getline(inFile, line)) {
            if (line == target) break;
        }
        inFile.close();
        
        auto stop = high_resolution_clock::now();
        searchTimes.push_back(duration_cast<microseconds>(stop - start).count());
    }

    remove(tempFile.c_str());
    return calculateStats(searchTimes);
}