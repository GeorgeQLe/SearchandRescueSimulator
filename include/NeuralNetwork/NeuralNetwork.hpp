/*  Copyright 2018 George Le

*/
#ifndef NEURALNETWORK_HPP
#define NEURALNETWORK_HPP

#include <map> // std::map
#include <memory> // std::shared_ptr
#include <string> // std::string
#include <vector> // std::vector

#include "NeuralNetwork/Neuron.hpp"

namespace nsNeuralNetwork {
    struct NeuralNetworkInformation {
        NeuralNetworkInformation() {}
        NeuralNetworkInformation(unsigned num_of_layers, unsigned neural_network_id) : m_num_of_layers(num_of_layers), m_neural_network_id(neural_network_id) { }
        
        unsigned m_num_of_layers = 0;
        unsigned m_neural_network_id = 0;
    };

    using NeuralNetworkLayer = std::vector<nsNeuron::Neuron>;
    using NeuralNetworkLayers = std::map<unsigned int, NeuralNetworkLayer>;
    struct NeuralNetworkLayerConstructionResult {
        NeuralNetworkLayerConstructionResult() { }
        NeuralNetworkLayerConstructionResult(const std::string& error_message) : m_has_error(true), m_error_message(error_message) { }
        bool m_has_error = false;
        std::string m_error_message = "NeuralNetwork: Hasn't hit an error yet";
    };

    struct NeuralNetworkReturnBool {
        NeuralNetworkReturnBool(bool final_value) : m_final_value(final_value) { }
        NeuralNetworkReturnBool(bool has_error, std::string error_message) : m_has_error(has_error), m_error_message(error_message) { }
        bool m_final_value = false;
        bool m_has_error = false;
        std::string m_error_message = "NeuralNetwork: Hasn't hit an error yet";
    };

    struct NeuralNetworkReturnDouble {
        NeuralNetworkReturnDouble(double final_value) : m_final_value(final_value) { }
        NeuralNetworkReturnDouble(bool has_error, std::string error_message) : m_has_error(has_error), m_error_message(error_message) { }
        double m_final_value = -1.0;
        bool m_has_error = false;
        std::string m_error_message = "NeuralNetwork: Hasn't hit an error yet";
    };

    class NeuralNetwork {
        public:
        NeuralNetwork() { }
        NeuralNetwork(unsigned int num_of_layers, unsigned int neural_network_id) : m_neural_network_information(num_of_layers ,neural_network_id){ }
        NeuralNetwork(const NeuralNetworkLayers& neural_network_layers, unsigned int num_of_layers, unsigned int neural_network_id) : m_neural_network_information(num_of_layers, neural_network_id), m_neural_network_layers(neural_network_layers) { }

        // mutator functions
        void set_neural_network_id(unsigned int neural_network_id) { m_neural_network_information.m_neural_network_id = neural_network_id; }

        NeuralNetworkLayerConstructionResult add_new_layer(unsigned int index_layer, const NeuralNetworkLayer& new_layer_of_neurons);
        NeuralNetworkLayerConstructionResult overwrite_layer(unsigned int index_layer, const NeuralNetworkLayer& replacement_layer_of_neurons);

        bool connecting_to_prev_layer(unsigned int current_layer_index);
        bool connecting_to_next_layer(unsigned int current_layer_index);

        bool verify_connections();

        NeuralNetworkReturnBool evaluate_bool(const std::vector<bool>& input_values);
        NeuralNetworkReturnBool evaluate_bool(const std::vector<double>& input_values, double radix_point);
        NeuralNetworkReturnDouble evaluate_double(const std::vector<double>& input_values);

        private:
        NeuralNetworkInformation m_neural_network_information;
        NeuralNetworkLayers m_neural_network_layers;
    };

    using NeuralNetworkptr = std::shared_ptr<NeuralNetwork>;
}

#endif