#include "network.h"
#include <cassert>
#include <iostream>

double net::ReLU(double x) {
    if (x > 0) {
        return x;
    } else {
        return 0;
    }
}

net::Neuron::Neuron(int numWeights) {
    inputWeights.resize(numWeights + 1);  // + 1 for bias
}

void net::Neuron::feedForward(std::vector<double> &inputs) {
    output = 0;
    assert(inputs.size() == inputWeights.size() - 1);  // - 1 for bias
    for (int i = 0; i < inputs.size(); ++i) {
        output += inputs[i] * inputWeights[i];
    }
    output += inputWeights[inputWeights.size() - 1];  // bias
    output = net::ReLU(output);
}

net::Network::Network(std::vector<int> &topology) {
    // set number of neurons / layer, and number of inputweights / neuron
    layers.resize(topology.size()); // number of layers
    for (int i = 0; i < layers.size(); ++i) {
        if (i == 0) {  // first layer all input sizes are 1
            for (int j = 0; j < topology[i]; ++j) {
                layers[i].push_back(net::Neuron(1));
                // std::cout<<i;
                std::cout<<layers[i][j].inputWeights.size();
            }
            layers[i].push_back(net::Neuron(0)); // bias?
        } else {  // other layers each neuron has input weight size of previous layer
            for (int j = 0; j < topology[i]; ++j) {
                layers[i].push_back(net::Neuron(layers[i - 1].size() - 1)); // first -1 to get prev layer. second to cancel bias compensation by neuron()
                // std::cout<<i;
                std::cout<<layers[i][j].inputWeights.size();
            }
            layers[i].push_back(net::Neuron(0)); // bias?
        }
        std::cout<<std::endl;
    }
}

void net::Network::feedForward(std::vector<double> &input) {
    // feed the inputs to the first layer:
    assert(input.size() == layers[0].size());
    for (int i = 0; i < input.size(); ++i) {
        //layers[0][i].feedForward
    }
    for (Layer l : layers) {
    }
}