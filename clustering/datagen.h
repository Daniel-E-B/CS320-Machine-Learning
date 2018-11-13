#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

namespace dataGen { // also has some processing
    void saveCSV(std::vector<std::vector<double>> data, std::string name);

    std::vector<std::vector<double>> generateRandom(int maxX, int maxY, int minX, int minY, int numPts);
    double scaleBetween(double unscaledNum, double minAllowed, double maxAllowed, double min, double max);
    double distance(std::vector<double> p1, std::vector<double> p2);

    /*
     * generates numClusters clusters at random locations.
     * spread controls the random distance of each point from the cluster center
     * numPts specifies the number of points in a cluster
     * works well enough, but can go over min and max due to spread, but this is fine for my use
     */
    std::vector<std::vector<double>>
    generateClusters(int maxX, int maxY, int minX, int minY, int numPts, int numClusters, int numNoise, double spread);
}