#include <iostream>
#include <vector>
#include "network.h"

int main() {
    std::vector<int> topology = {2, 1};
    net::Network mynet(topology, 0.03);
    std::vector<std::vector<double>> inputs = {{1., 1.}, {0., 0.}, {1., 0.}, {0., 1.}};
    std::vector<std::vector<double>> desiredOut = {{-1.}, {-1.}, {1.}, {1.}};
    std::vector<double> outputs;
    float numCorrect = 0;
    for (int epochs = 0; epochs < 100; ++epochs) {
        for (int i = 0; i < 4; ++i) {
            outputs = mynet.feedForward(inputs[i]);
            std::cout << "epoch: " << epochs << ", actual: " << outputs[0] << ", desired: " << desiredOut[i][0] << std::endl;
            mynet.backProp(desiredOut[i]);
        }
    }
    return 0;
}