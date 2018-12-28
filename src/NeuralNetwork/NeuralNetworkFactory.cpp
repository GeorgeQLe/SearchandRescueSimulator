/*  Copyright 2018 George Le

*/
#include <iostream>

#include "NeuralNetwork/NeuralNetworkFactory.hpp"

nsNeuralNetworkFactory::NeuralNetworkLayerSizes::NeuralNetworkLayerSizes(const std::vector<unsigned int>& neural_network_ratio)  {
    if(neural_network_ratio.at(neural_network_ratio.size() - 1) != 1) {
        std::cout << "The last layer of the neural network is not of size 1.\n";
        return;
    }
    else if (neural_network_ratio.at(neural_network_ratio.size() - 1) == 1) {
        m_neural_network_ratio = neural_network_ratio;
    }
}

nsNeuralNetwork::NeuralNetwork nsNeuralNetworkFactory::NeuralNetworkFactory::construct_neural_network(unsigned int num_layers, nsNeuralNetworkFactory::NeuralNetworkLayerSizes layer_sizes) {
    // creates an empty neural network with an ID, the tracked ID is then incremented.
    nsNeuralNetwork::NeuralNetwork return_network(num_layers, this->m_current_neural_network_id++);
    nsNeuralNetwork::NeuralNetworkLayer neuron_layer;

    for(unsigned int i = 0; i < num_layers; ++i) {
        for(unsigned int j = 0; j < layer_sizes.m_neural_network_ratio.at(i); ++j) {
            neuron_layer.push_back(nsNeuron::Neuron());
        }
        return_network.add_new_layer(i, neuron_layer);
    }
    return return_network;
}