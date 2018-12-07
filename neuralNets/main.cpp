#include <vector>
#include "network.h"

int main() {
    std::vector<int> topology = {1, 2};
    net::Network mynet(topology);
    std::vector<double> inputs = {1};
    mynet.feedForward(inputs);
    return 0;
}