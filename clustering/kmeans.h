#include <vector>

class KMeans {
public:
    KMeans(int numClusters_, double threshold_);

    int numClusters; // number of clusters to find. If extra time, try multiple and optimize
    double threshold; // when to stop iterating.
    std::vector<std::vector<std::vector<double>>> cluster(std::vector<std::vector<double>> data); // list of clusters. each one has a list of xy pts

};