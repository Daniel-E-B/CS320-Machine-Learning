#include <vector>

class Point {
public:
    Point(std::vector<double> pos_, int id_);
    std::vector<Point> neighbors; // pts within maxDist
    std::vector<double> pos;
    bool noise = true;
    int id; // random identifier to differentiate points
};

typedef std::vector<Point> Cluster;

class DBscan {
public:
    DBscan(double maxDist_, int minPts_);
    std::vector<Cluster> scan(std::vector<std::vector<double>> data); // xy pairs of cluster c
private:
    double maxDist;
    int minPts;
};