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
    assert(inputs.size() == inputWeights.size());
    for (int i = 0; i < inputs.size(); ++i) {
        output += inputs[i] * inputWeights[i];
    }
    //output += inputWeights[inputWeights.size() - 1];  // bias I THINK THIS IS ALREADY TAKEN CARE OF
    output = net::ReLU(output);
}

net::Network::Network(std::vector<int> &topology) {
    // set number of neurons / layer, and number of inputweights / neuron
    layers.resize(topology.size());  // number of layers
    for (int i = 0; i < layers.size(); ++i) {
        if (i == 0) {  // first layer all input sizes are 1
            for (int j = 0; j < topology[i]; ++j) {
                layers[i].push_back(net::Neuron(1));
            }
            layers[i].push_back(net::Neuron(0));  // bias?
        } else {                                  // other layers each neuron has input weight size of previous layer
            for (int j = 0; j < topology[i]; ++j) {
                layers[i].push_back(net::Neuron(layers[i - 1].size() - 1));  // first -1 to get prev layer. second to cancel bias compensation by neuron()
            }
            layers[i].push_back(net::Neuron(0));  // bias?
        }
    }
}

void net::Network::feedForward(std::vector<double> &input) {
    assert(input.size() == layers[0].size() - 1);  // -1 for bias
    for (int i = 0; i < layers.size(); ++i) {
        // feed the inputs to the first layer:
        if (i == 0) {
            for (int j = 0; j < input.size(); ++j) {
                std::vector<double> fullInput = {input[j], 1};  // 1 for the bias
                layers[i][j].feedForward(fullInput);
            }
        }
        
        // pass stuff forward
        else /*if (i < layers.size() - 1)*/ {
            // get outputs from prev layer
            std::vector<double> prevOutputs;
            for (int j = 0; j < layers[i - 1].size(); ++j) {
                prevOutputs.push_back(layers[i - 1][j].output);
            }
            // bias is already added, so no need to add it here
            // feed to next layer
            for (int j = 0; j < layers[i].size() - 1; ++j) {
                layers[i][j].feedForward(prevOutputs);
            }
        }
    }
}