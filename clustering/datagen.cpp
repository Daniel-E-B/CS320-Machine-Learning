#include <cmath>
#include <iostream>
#include "datagen.h"

using namespace dataGen;

double dataGen::scaleBetween(double unscaledNum, double minAllowed, double maxAllowed, double min, double max) {
    return (maxAllowed - minAllowed) * (unscaledNum - min) / (max - min) + minAllowed;
}

double dataGen::distance(std::vector<double> p1, std::vector<double> p2) {
    // it returns nan sometimes. probably overflow. maybe I should use a dataset with a smaller range?
    return sqrt(pow(p1[0] - p2[0], 2) + pow(p1[1] - p2[1], 2));
}

void dataGen::saveCSV(std::vector<std::vector<double>> data, std::string name) {
    std::ofstream outFile(name + ".csv");
    for (std::vector<double> row : data) {
        for (double val : row) {
            outFile << std::to_string(val) << ",";
        }
        outFile << "\n";
    }
    outFile.close();
}

std::vector<std::vector<double>> dataGen::generateRandom(int maxX, int maxY, int minX, int minY, int numPts) {
    std::srand(std::time(nullptr)); // current time = random seed
    std::vector<std::vector<double>> data;
    for (int i = 0; i < numPts; ++i) {
        data.push_back({scaleBetween(std::rand(), minX, maxX, 0, RAND_MAX),
                        scaleBetween(std::rand(), minY, maxY, 0, RAND_MAX)});
    }
    return data;
}

std::vector<std::vector<double>>
dataGen::generateClusters(int maxX, int maxY, int minX, int minY, int numPts, int numClusters, int numNoise, double spread) {
    std::srand(std::time(nullptr)); // current time = random seed
    std::vector<std::vector<double>> data;
    for (int i = 0; i < numClusters; ++i) {
        int clusterX = scaleBetween(std::rand(), minX, maxX, 0, RAND_MAX);
        int clusterY = scaleBetween(std::rand(), minY, maxY, 0, RAND_MAX);
        for (int j = 0; j < numPts; ++j) {
            data.push_back(
                    {scaleBetween(std::rand(), clusterX - spread, clusterX + spread, 0, RAND_MAX),
                     scaleBetween(std::rand(), clusterY - spread, clusterY + spread, 0, RAND_MAX)});
        }
    }
    for (int i = 0; i < numNoise; ++i) {
        data.push_back({scaleBetween(std::rand(), minX, maxX, 0, RAND_MAX),
                        scaleBetween(std::rand(), minY, maxY, 0, RAND_MAX)});
    }
    return data;
}