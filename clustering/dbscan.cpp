#include "dbscan.h"

DBscan::DBscan(double maxDist_, int minPts_) {
    maxDist = maxDist_;
    minPts = minPts_;
}

std::vector<Point> DBscan::scan(std::vector<std::vector<double>> data) {

}