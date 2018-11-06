#include <vector>
#include <string>
#include <fstream>
// TODO: DOUBLES instead of strings
namespace csv {
    std::vector<std::vector<std::string>> parse(std::string fileName, char sep) {
        std::ifstream inFile(fileName);
        std::vector<std::vector<std::string>> data;
        std::string strLine;
        if (inFile.is_open()) {
            while (getline(inFile, strLine)) {
                std::string tempVal = "";
                std::vector<std::string> vecLine;
                for (char c : strLine) {
                    if (c != sep) {
                        tempVal += c;
                    } else {
                        vecLine.push_back(tempVal);
                        tempVal = "";
                    }
                }
                data.push_back(vecLine);
            }
            inFile.close();
        }
        return data;
    }
}