#include <vector>

class Point {
public:
    Point(std::vector<double> pos, int id);
    std::vector<Point> neighbors; // pts within maxDist
    std::vector<double> pos;
    bool noise = true;
    int id; // random identifier to differentiate points
};

typedef std::vector<Point> Cluster;

class DBscan {
public:
    DBscan(double maxDist, int minPts);
    std::vector<Cluster> scan(std::vector<std::vector<double>> data); // xy pairs of cluster c
    double distance(Point p1, Point p2);
private:
    double maxDist;
    int minPts;
};