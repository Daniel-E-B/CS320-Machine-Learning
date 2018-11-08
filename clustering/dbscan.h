#include <vector>

class Point {
public:

};

class DBscan {
public:
    DBscan(double maxDist, int minPts);
    std::vector<Point> scan(std::vector<std::vector<double>> data);
private:
    double maxDist;
    int minPts;
};