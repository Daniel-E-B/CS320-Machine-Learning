#include <vector>
#include <cmath>
#include "dbscan.h"
#include "datagen.h"

Point::Point(std::vector<double> pos_, int id_) {
    pos = pos_;
    id = id_;
}


DBscan::DBscan(double maxDist_, int minPts_) {
    maxDist = maxDist_;
    minPts = minPts_;
}

std::vector<Cluster> DBscan::scan(std::vector<std::vector<double>> data) {
    std::vector<Cluster> clusters;
    // convert data2d to pts2d
    std::vector<Point> points;
    int id = 0;
    for (std::vector<double> pos : data) {
        points.push_back(Point(pos, id));
        ++id;
    }

    // iterate through points and fill in params
    for (Point outerPt : points) {
        for (Point innerPt : points) {
            if (outerPt.id != innerPt.id) {
                if (dataGen::distance(outerPt.pos, innerPt.pos) < maxDist) {
                    // "count" neighbors
                    outerPt.neighbors.push_back(innerPt);
                }
            }
            // if there are enough neighbors, give new cluster label, otherwise label as noise
            if (outerPt.neighbors.size() > minPts) {
                clusters.push_back({outerPt});
            } else {
                outerPt.noise = true;
            }

        }
    }
    // the following should be a function given cluster that returns an updated version of cluster
    for (Cluster cluster : clusters) {
        for (Point corePt : cluster) {
            // for each of this points neighbor points,
            for (Point neighborPt : corePt.neighbors) {
                // if the neighbor already has a label other than noise, move on to the next neighbor
                // otherwise, give the neighbor the same new cluster label
                if (neighborPt.noise) {
                    cluster.push_back(neighborPt);
                }
                // if the neighbor has more than the minimum number of neighbors, add all of them to the list of neighbors
                // for this cluster, so that they go through this same loop... This should have been "covered" but might also result in too many clusters
            }
        }
    }
    return clusters;
}