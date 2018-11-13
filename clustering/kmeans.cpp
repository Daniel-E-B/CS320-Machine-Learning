#include <vector>
#include <cmath>
#include <iostream>
#include "kmeans.h"
#include "datagen.h"

KMeans::KMeans(int numClusters_, double threshold_) {
    numClusters = numClusters_;
    threshold = threshold_;
}

std::vector<std::vector<std::vector<double>>> KMeans::cluster(std::vector<std::vector<double>> data) {
    std::srand(std::time(nullptr)); // current time = random seed
    std::vector<std::vector<double>> centroids;
    std::vector<std::vector<std::vector<double>>> clusters(numClusters);
    for (int i = 0; i < numClusters; ++i) {
        // find max and min of x and y
        double minX = data[0][0], minY = data[0][1], maxX = 0, maxY = 0;
        for (std::vector<double> pt : data) {
            if (pt[0] > maxX) {
                maxX = pt[0];
            }
            if (pt[0] < minX) {
                minX = pt[0];
            }
            if (pt[1] > maxY) {
                maxY = pt[1];
            }
            if (pt[1] < minY) {
                minY = pt[1];
            }
        }
        // place random centroid
        centroids.push_back({dataGen::scaleBetween(std::rand(), minX, maxX, 0, RAND_MAX),
                             dataGen::scaleBetween(std::rand(), minY, maxY, 0, RAND_MAX)});
    }
    std::vector<double> motion(numClusters);
    // how far each centroid is moving. centroid should probably be a custom datatype

    // repeat until centroids are moving less than threshold distance
    double avg = threshold + 1;
    while (avg > threshold) {
       // clusters.clear(); TODO: shouldn't this be cleared each time, because otherwise points will be in multiple clusters?
        for (std::vector<double> pt : data) {
            // find which centroid it is closest to.
            int index = 0;
            double dist = dataGen::distance(centroids[0], pt);
            for (int i = 0; i < centroids.size(); ++i) {
                std::vector<double> centroid = centroids[i];
                if (dataGen::distance(centroid, pt) < dist) {
                    index = i;
                }
            }
            // move to that index of clusters
            clusters[index].push_back(pt);
        }
        // recompute centroids
        for (int i = 0; i < centroids.size(); ++i) {
            double x = 0, y = 0;
            for (std::vector<double> pt : clusters[i]) {
                x += pt[0];
                y += pt[1];
            }
            std::vector<double> oldPos = centroids[i];
            centroids[i] = {x / clusters[i].size(), y / clusters[i].size()};
            motion[i] = dataGen::distance(oldPos, centroids[i]);
            std::cout << "i: " << i << ": " << motion[i] << std::endl;
        }
        // set the average
        double sum = 0;
        for (double dist : motion) {
            sum += dist;
        }
        avg = sum / (double) numClusters;
        std::cout << "avg: " << avg << std::endl;

    }
    return clusters;
}