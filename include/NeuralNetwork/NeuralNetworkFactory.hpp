/*  Copyright 2018 George Le

    This file provides the declaration of the namespace nsNeuralNetworkFactory,
    which includes the struct NeuralNetworkLayerSizes and the class NeuralNetworkFactory.
*/
#ifndef NEURALNETWORKFACTORY_HPP
#define NEURALNETWORKFACTORY_HPP

#include "NeuralNetwork/NeuralNetwork.hpp"

namespace nsNeuralNetworkFactory {
    
    struct NeuralNetworkLayerSizes {
        NeuralNetworkLayerSizes(const std::vector<unsigned int>& neural_network_ratio);
        std::vector<unsigned int> m_neural_network_ratio;
    };

    class NeuralNetworkFactory {
    public:
    static NeuralNetworkFactory& get_instance() {
        static NeuralNetworkFactory instance;
        return instance;
    }

    nsNeuralNetwork::NeuralNetwork construct_neural_network(unsigned int num_layers, nsNeuralNetworkFactory::NeuralNetworkLayerSizes layer_ratios);

    private:
    NeuralNetworkFactory() { }

    unsigned int m_current_neural_network_id = 1;
};
}

#endif