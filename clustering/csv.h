#include <vector>
#include <string>
#include <fstream>

namespace csv {
    std::vector<std::vector<double>> parse(std::string fileName, char sep);
}