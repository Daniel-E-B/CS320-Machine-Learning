#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

namespace dataGen {
    void saveCSV(std::vector<std::vector<double>> data, std::string name);

    std::vector<std::vector<double>> generateRandom(int maxX, int maxY, int minX, int minY, int numPts);

    /*
     * generates numClusters clusters at random locations.
     * spread controls the random distance of each point from the cluster center
     * numPts specifies the number of points in a cluster
     * works well enough, but can go over min and max due to spread, but this is fine for my use
     */
    std::vector<std::vector<double>>
    generateClusters(int maxX, int maxY, int minX, int minY, int numPts, int numClusters, int numNoise, double spread);
}