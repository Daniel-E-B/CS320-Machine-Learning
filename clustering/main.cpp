#include <iostream>
#include "csv.h"
#include "datagen.h"

int main() {
    std::string dataFile = "/Users/danbern/Documents/programming/CS320-Machine-Learning/data/00320uciedu/student-mat.csv";
    std::vector data = csv::parse(dataFile, ';');
    for (std::vector<std::string> row : data) {
        for (std::string value : row) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
    dataGen::saveCSV(dataGen::generateRandom(500, 500, 0, 0, 1000), "random");
    dataGen::saveCSV(dataGen::generateClusters(500, 500, 0, 0, 250, 5, 50), "clustered");
    return 0;
}