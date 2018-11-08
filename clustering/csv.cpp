#include "csv.h"

using namespace csv;

std::vector<std::vector<double>> csv::parse(std::string fileName, char sep) {
    std::ifstream inFile(fileName);
    std::vector<std::vector<double>> data;
    std::string strLine;
    if (inFile.is_open()) {
        while (getline(inFile, strLine)) {
            std::string tempVal = "";
            std::vector<double> vecLine;
            for (char c : strLine) {
                if (c != sep) {
                    tempVal += c;
                } else {
                    vecLine.push_back(std::stod(tempVal));
                    tempVal = "";
                }
            }
            data.push_back(vecLine);
        }
        inFile.close();
    }
    return data;
}