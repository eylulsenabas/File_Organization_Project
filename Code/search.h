#ifndef SEARCH_H
#define SEARCH_H

#include <string>
#include <vector>

struct SearchResult {
    double averageTime;
    long long maxTime;
    double stdDev;
};

SearchResult searchInRaw(const std::vector<std::string>& targets);
SearchResult searchInHashed(const std::vector<std::string>& targets);
SearchResult searchInCompressed(const std::vector<std::string>& targets, long long& decompressTime);

#endif