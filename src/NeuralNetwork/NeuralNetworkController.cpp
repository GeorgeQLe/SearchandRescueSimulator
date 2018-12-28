/*  Copyright 2018 George Le

*/
#include "NeuralNetwork/NeuralNetworkController.hpp"

void nsNeuralNetworkController::NeuralNetworkController::set_neural_network(const nsNeuralNetwork::NeuralNetworkptr& new_network) {
    m_neural_networks.push_back(new_network);
}

std::vector<bool> nsNeuralNetworkController::NeuralNetworkController::evaluate_bool(const std::vector<bool>& input_values) {
    std::vector<bool> list;
    for(unsigned int i = 0; i < this->m_neural_networks.size(); ++i) {
        list.push_back(this->m_neural_networks.at(i)->evaluate_bool(input_values).m_final_value);
    }
    return list;
}

std::vector<double> nsNeuralNetworkController::NeuralNetworkController::evaluate_double(const std::vector<double>& input_values) {
    std::vector<double> list;
    for(unsigned int i = 0; i < this->m_neural_networks.size(); ++i) {
        list.push_back(this->m_neural_networks.at(i)->evaluate_double(input_values).m_final_value);
    }
    return list;
}
