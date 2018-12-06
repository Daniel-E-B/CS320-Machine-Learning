#include <vector>
#include "network.h"

int main() {
    std::vector<int> topology = {6, 5, 4, 3, 2};
    net::Network mynet(topology);
    std::vector<double> inputs = {1, 2, 3, 4, 5, 6};
    mynet.feedForward(inputs);
    return 0;
}