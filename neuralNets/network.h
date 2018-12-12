// inspired in part by: https://mattmazur.com/2015/03/17/a-step-by-step-backpropagation-example/

#include <vector>

namespace net {
double ReLU(double x);
double dReLU(double x);

class Neuron {
   public:
    Neuron(int numWeights);
    std::vector<double> inputWeights;
    double output;
    void feedForward(std::vector<double> &inputs, double bias);
};

typedef std::vector<Neuron> Layer;

class Network {
   private:
    std::vector<Layer> layers;
    std::vector<double> biases;
    std::vector<double> recentInputs; // lol for debugging

   public:
    Network(std::vector<int> &topology, double lr);  // configure network
    double learningRate;
    std::vector<double> feedForward(std::vector<double> input);
    void backProp(std::vector<double> &desiredOutput);
};
}  // namespace net