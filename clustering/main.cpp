#include <iostream>
#include "csv.h"
#include "datagen.h"

/*
 * I chose to hardcode this for 2d data of doubles, because it was very easy to check in spreadsheet software
 * TODO: if i have extra time, make it word for n dimensional data
 */

int main() {
    std::string dataFile = "/Users/danbern/Documents/programming/CS320-Machine-Learning/data/clustered.csv";
    std::vector data = csv::parse(dataFile, ',');



//    for (std::vector<double> row : data) {
//        for (double value : row) {
//            std::cout << std::to_string(value) << ", ";
//        }
//        std::cout << std::endl;
//    }
    // dataGen::saveCSV(dataGen::generateRandom(500, 500, 0, 0, 1000), "random");
    // dataGen::saveCSV(dataGen::generateClusters(1000, 1000, 0, 0, 300, 5, 100, 100), "clustered");
    return 0;
}