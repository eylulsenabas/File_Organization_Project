#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

long long getFileSize(const std::string& filepath);
std::string calculateMD5(const std::string& input);

std::vector<std::string> getRandomPasswords(int count);
double getMemoryUsageMB();

#endif