#include <vector>

namespace net {
double ReLU(double x);

class Neuron {
   public:
    Neuron(int numWeights);
    std::vector<double> inputWeights;
    double output;
    void feedForward(std::vector<double> &inputs);  // need to set weights somewhere though
};

typedef std::vector<Neuron> Layer;

class Network {
   private:
    std::vector<Layer> layers;

   public:
    Network(std::vector<int> &topology); // configure network
    void feedForward(std::vector<double> &input);
    void backProp(std::vector<double> &desiredOutput);
};
}  // namespace net