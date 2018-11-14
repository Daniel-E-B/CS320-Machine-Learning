#include <iostream>
#include <fstream>
#include "csv.h"
#include "datagen.h"
#include "dbscan.h"
#include "kmeans.h"

/*
 * I chose to hardcode this for 2d data of doubles, because it was very easy to check in spreadsheet software
 * TODO: if i have extra time, make it work for n dimensional data
 * TODO: const qualify things that don't need to change, and have them be passed as references
 * TODO: change DBscan return type to the same as KMeans so that it can return a list of clusters (requires smol rewrite)
 */

int main() {
    std::string dataFile = "/Users/danbern/Documents/programming/CS320-Machine-Learning/data/clustered.csv";
    std::vector data = csv::parse(dataFile, ',');

//    DBscan scanner(10, 5); // 10 maxdist 5 minpts
//    std::vector<Cluster> clusters = scanner.scan(data);
//
//    std::ofstream clusterFile;
//    clusterFile.open("clusters.csv");
//
//    for (Cluster c : clusters) {
//        for (Point p : c) {
//            std::cout << p.pos[0] << ", " << p.pos[1] << std::endl;
//            clusterFile << p.pos[0] << ", " << p.pos[1] << "\n";
//        }
//        //break;
//    }
//    clusterFile.close();

    KMeans clusterer(5, 1); // 5 clusters, 1 threshold
    std::vector<std::vector<std::vector<double>>> clusters = clusterer.cluster(data);
    std::cout << "CLUSTERED" << std::endl;

    std::ofstream clusterFile;
    clusterFile.open("Kmeansed.csv");

    for (std::vector<std::vector<double>> cluster : clusters) {
        for (std::vector<double> pt : cluster) {
            clusterFile << pt[0] << "," << pt[1] << "\n";
        }
        clusterFile << "b\nb\nb\nb\n"; // sometimes the clusters are empty?! maybe two are in the same place
        std::cout << "cluster written" << std::endl;
    }

    clusterFile.close();


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