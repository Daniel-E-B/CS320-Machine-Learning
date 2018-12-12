#include "network.h"
#include <cassert>
#include <cmath>
#include <iostream>
#include <random>

// changed to tanh because ReLU was being annoying
// didn't bother to refactor naming because VS code is 🅱️ad

double net::ReLU(double x) {
    // return x > 0 ? x : 0;
    return tanh(x);
}

double net::dReLU(double x) {
    // return x > 0 ? 1 : 0;
    return 1 - pow(tanh(x), 2);
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
    std::normal_distribution<> dis(0, RAND_MAX);
    for (double &w : inputWeights) {
        w = double(dis(gen)) / RAND_MAX / 100.0 + 0.01;
    }
}

void net::Neuron::feedForward(std::vector<double> &inputs, double bias) {
    output = 0;
    assert(inputs.size() == inputWeights.size());
    for (int i = 0; i < inputs.size(); ++i) {
        output += inputs[i] * inputWeights[i];
    }
    output = net::ReLU(output + bias);
    // output = tanh(output);
}

net::Network::Network(std::vector<int> &topology, double lr) {
    learningRate = lr;
    // set number of neurons / layer, and number of inputweights / neuron
    layers.resize(topology.size());  // number of layers
    biases.resize(topology.size());
    std::fill(biases.begin(), biases.end(), 0.01);  // common practice = all 0 or all 0.01 so the relus fire (stanford cs231n)
    for (int i = 0; i < layers.size(); ++i) {
        if (i == 0) {  // first layer all input sizes are 1
            for (int j = 0; j < topology[i]; ++j) {
                layers[i].push_back(net::Neuron(1));
            }
        } else {  // other layers each neuron has input weight size of previous layer
            for (int j = 0; j < topology[i]; ++j) {
                layers[i].push_back(net::Neuron(layers[i - 1].size()));  //  -1 to get prev layer
            }
        }
    }
}

std::vector<double> net::Network::feedForward(std::vector<double> &input) {
    recentInputs = input;  // might have reference issues
    std::vector<std::vector<double>> firstLayerInputs = {};
    for (int i = 0; i < input.size(); ++i) {
        firstLayerInputs.push_back({});
        firstLayerInputs[i].push_back(input[i]);
    }
    assert(input.size() == layers[0].size());
    for (int i = 0; i < layers.size(); ++i) {
        // feed the inputs to the first layer:
        if (i == 0) {
            for (int j = 0; j < input.size(); ++j) {
                layers[i][j].feedForward(firstLayerInputs[j], biases[i]);
                // layers[i][j].feedForward(firstLayerInputs[j], 0); // got rid of biases to simplify
            }
        }

        // pass stuff forward
        else {
            // get outputs from prev layer
            std::vector<double> prevOutputs;
            for (int j = 0; j < layers[i - 1].size(); ++j) {
                prevOutputs.push_back(layers[i - 1][j].output);
            }
            // feed to next layer
            for (int j = 0; j < layers[i].size(); ++j) {
                layers[i][j].feedForward(prevOutputs, biases[i]);
                // layers[i][j].feedForward(prevOutputs, 0);
            }
        }
    }
    std::vector<double> outputs = {};
    for (int i = 0; i < layers[layers.size() - 1].size(); ++i) {
        outputs.push_back(layers[layers.size() - 1][i].output);
    }
    return outputs;
    // std::cout << "Fed forward:" << std::endl;
    // for (double val : input) {
    //     std::cout << val << ",";
    // }
    // std::cout << std::endl
    //           << "input weights: " << std::endl;
    // for (Layer l : layers) {
    //     for (net::Neuron n : l) {
    //         for (double w : n.inputWeights) {
    //             std::cout << w << ",";
    //         }
    //     }
    //     std::cout << std::endl
    //               << std::endl;
    // }
    // std::cout << "outputs: " << std::endl;
    // for (int i = 0; i < layers.size(); ++i) {
    //     Layer l = layers[i];
    //     std::cout << "layer size: " << l.size() << std::endl;
    //     for (net::Neuron n : l) {
    //         std::cout << n.output << ",";
    //     }
    //     std::cout << std::endl
    //               << "bias: " << biases[i] << std::endl;
    // }
}

// http://techeffigytutorials.blogspot.com/2015/01/neural-network-illustrated-step-by-step.html
void net::Network::backProp(std::vector<double> &desiredOutput) {
    assert(desiredOutput.size() == layers[layers.size() - 1].size());

    // std::cout << "backpropping" << std::endl;

    std::vector<std::vector<double>> errors;  // in reverse order?
    std::vector<double> errorLayer;
    for (int i = layers.size() - 1; i >= 0; --i) {
        // std::cout<<i<<std::endl;
        if (i == layers.size() - 1) {
            errorLayer = {};
            for (int j = 0; j < layers[i].size(); ++j) {
                // std::cout << "neuron " << j << "/"<<layers[i].size()<<", layer " << i << std::endl;
                // std::cout << "desired out: " << desiredOutput[j] << std::endl;
                // std::cout << "actual output: " << layers[i][j].output << std::endl;
                // std::cout << "dRelu of actual output: " << dReLU(layers[i][j].output) << std::endl;
                errorLayer.push_back((desiredOutput[j] - layers[i][j].output) * dReLU(layers[i][j].output));
            }
            errors.push_back(errorLayer);
            // std::cout << "errors from last layer pushed back" << std::endl
            //   << std::endl;
        } else {
            errorLayer = {};

            for (int j = 0; j < layers[i].size(); ++j) {  // find the error for each node in the layer
                errorLayer.push_back(0);
                for (int k = 0; k < layers[i + 1].size(); ++k) {  // get the inputweights of the nodes in the next layer
                    errorLayer[j] += layers[i + 1][k].inputWeights[j] * layers[i][k].output;
                }
                errorLayer[j] *= dReLU(layers[i][j].output);
            }
            errors.push_back(errorLayer);
        }
    }
    // std::cout << "computed errors"<<std::endl;
    // update the weights
    // go through each layer
    for (int i = 0; i < layers.size(); ++i) {
        // go through each neuron
        for (int j = 0; j < layers[i].size(); ++j) {
            // go through each weight
            for (int k = 0; k < layers[i][j].inputWeights.size(); ++k) {
                if (i == 0) {
                    layers[i][j].inputWeights[k] = layers[i][j].inputWeights[k] + learningRate * errors[layers.size() - 1 - i][j] * recentInputs[j];
                } else {
                    layers[i][j].inputWeights[k] = layers[i][j].inputWeights[k] + learningRate * errors[layers.size() - 1 - i][j] * layers[i][j].output;
                    // std::cout<<layers[i][j].output<<",";
                }
            }
            // std::cout<<"    ";
        }
        // std::cout<<std::endl;
    }
}