#include <vector>
#include <string>
#include <fstream>
// TODO: DOUBLES instead of strings
namespace csv {
    std::vector<std::vector<double>> parse(std::string fileName, char sep);
}