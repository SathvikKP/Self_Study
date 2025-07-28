#include "utils/utils.h"
#include <fstream>

std::vector<int> readIntegersFromFile(const std::string& filename) {
    std::vector<int> values;
    std::ifstream infile(filename);
    int x;
    while (infile >> x) {
        values.push_back(x);
    }
    return values;
}