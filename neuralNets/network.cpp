#include "network.h"
#include <cassert>
#include <cmath>
#include <iostream>
#include <random>

double net::ReLU(double x) {
    if (x > 0) {
        return x;
    } else {
        return 0;
    }
}

net::Neuron::Neuron(int numWeights) {
    inputWeights.resize(numWeights);
    // randomize weights:
    /*
        https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
        https://en.cppreference.com/w/cpp/numeric/random/normal_distribution
    */
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dis(-RAND_MAX, RAND_MAX);
    for (double &w : inputWeights) {
        w = double(dis(gen)) / double(RAND_MAX) / 100;
    }
}

void net::Neuron::feedForward(std::vector<double> &inputs) {
    output = 0;
    assert(inputs.size() == inputWeights.size());
    for (int i = 0; i < inputs.size(); ++i) {
        output += inputs[i] * inputWeights[i];
    }
    //output += inputWeights[inputWeights.size() - 1];  // bias I THINK THIS IS ALREADY TAKEN CARE OF
    output = net::ReLU(output);
    // output = tanh(output);
}

net::Network::Network(std::vector<int> &topology) {
    // set number of neurons / layer, and number of inputweights / neuron
    layers.resize(topology.size());  // number of layers
    for (int i = 0; i < layers.size(); ++i) {
        if (i == 0) {  // first layer all input sizes are 1
            for (int j = 0; j < topology[i]; ++j) {
                layers[i].push_back(net::Neuron(1));
            }
        } else {                                  // other layers each neuron has input weight size of previous layer
            for (int j = 0; j < topology[i]; ++j) {
                layers[i].push_back(net::Neuron(layers[i - 1].size()));  //  -1 to get prev layer
            }
        }
    }
}

void net::Network::feedForward(std::vector<double> &input) {
    assert(input.size() == layers[0].size());
    for (int i = 0; i < layers.size(); ++i) {
        // feed the inputs to the first layer:
        if (i == 0) {
            for (int j = 0; j < input.size(); ++j) {
                layers[i][j].feedForward(input);
            }
        }

        // pass stuff forward
        else {
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
    std::cout << "Fed forward:" << std::endl;
    for (double val : input) {
        std::cout << val << ",";
    }
    std::cout << std::endl
              << "input weights: " << std::endl;
    for (Layer l : layers) {
        for (net::Neuron n : l) {
            for (double w : n.inputWeights) {
                std::cout << w << ",";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "outputs: " << std::endl;
    for (Layer l : layers) {
        std::cout<<"layer size: "<<l.size()<<std::endl;
        for (net::Neuron n : l) {
            std::cout << n.output << ",";
        }
        std::cout << std::endl;
    }
}