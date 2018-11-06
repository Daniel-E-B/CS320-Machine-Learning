#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

double scaleBetween(double unscaledNum, double minAllowed, double maxAllowed, double min, double max) {
    return (maxAllowed - minAllowed) * (unscaledNum - min) / (max - min) + minAllowed;
}
// yes, I know I am using namespaces wrong(ish).

namespace dataGen {
    void saveCSV(std::vector<std::vector<double>> data, std::string name) {
        std::ofstream outFile(name + ".csv");
        for (std::vector<double> row : data) {
            for (double val : row) {
                outFile << std::to_string(val) << ",";
            }
            outFile << "\n";
        }
        outFile.close();
    }

    std::vector<std::vector<double>> generateRandom(int maxX, int maxY, int minX, int minY, int numPts) {
        std::srand(std::time(nullptr)); // current time = random seed
        std::vector<std::vector<double>> data;
        for (int i = 0; i < numPts; ++i) {
            data.push_back({scaleBetween(std::rand(), minX, maxX, 0, RAND_MAX),
                            scaleBetween(std::rand(), minY, maxY, 0, RAND_MAX)});
        }
        return data;
    }

    /*
     * generates numClusters clusters at random locations.
     * spread controls the random distance of each point from the cluster center
     * numPts specifies the number of points in a cluster
     * works well enough, but can go over min and max due to spread, but this is fine for my use
     */
    std::vector<std::vector<double>>
    generateClusters(int maxX, int maxY, int minX, int minY, int numPts, int numClusters, double spread) {
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
        return data;
    }
}