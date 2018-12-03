#include <vector>
#include "network.h"

int main() {
    std::vector<int> topology = {6, 5, 4, 3, 2};
    net::Network mynet(topology);
    return 0;
}