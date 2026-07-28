#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <string>

void compressData(const std::string& inFile, const std::string& outFile);
void decompressData(const std::string& inFile, const std::string& outFile);

#endif