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
        NeuralNetworkInformation(const NeuralNetworkInformation& information) : m_neural_network_id(information.m_neural_network_id), m_num_of_layers(information.m_num_of_layers) {}
        NeuralNetworkInformation(unsigned neural_network_id, unsigned num_of_layers) : m_neural_network_id(neural_network_id), m_num_of_layers(num_of_layers) { }
        
        bool operator==(const NeuralNetworkInformation& right) const {
            if(this->m_neural_network_id == right.m_neural_network_id) {
                if(this->m_num_of_layers == right.m_num_of_layers) {
                    return true;
                }
            }
            return false;
        }

        NeuralNetworkInformation operator=(const NeuralNetworkInformation& right) {
            this->m_neural_network_id = right.m_neural_network_id;
            this->m_num_of_layers = right.m_num_of_layers;

            return *this;
        };

        unsigned m_neural_network_id = 0;
        unsigned m_num_of_layers = 0;
    };

    struct NeuralNetworkLayerConstructionResult {
        NeuralNetworkLayerConstructionResult() { }
        NeuralNetworkLayerConstructionResult(const std::string& error_message) : m_has_error(true), m_error_message(error_message) { }
        
        bool m_has_error = false;
        std::string m_error_message = "NeuralNetwork: Hasn't hit an error yet";
    };

    template <typename T>
    struct NeuralNetworkReturnValue {
        NeuralNetworkReturnValue(T final_value) : m_final_value(final_value) { }
        NeuralNetworkReturnValue(bool has_error, std::string error_message) : m_has_error(has_error), m_error_message(error_message) { }
        
        T m_final_value;
        bool m_has_error = false;
        std::string m_error_message = "NeuralNetwork: Hasn't hit an error yet";
    };

    // struct NeuralNetworkReturnDouble {
    //     NeuralNetworkReturnDouble(double final_value) : m_final_value(final_value) { }
    //     NeuralNetworkReturnDouble(bool has_error, std::string error_message) : m_has_error(has_error), m_error_message(error_message) { }
        
    //     bool m_has_error = false;
    //     double m_final_value = -1.0;
    //     std::string m_error_message = "NeuralNetwork: Hasn't hit an error yet";
    // };

    template <typename T>
    using NeuralNetworkLayer = std::vector<nsNeuron::Neuron<T>>;
    // This struct holds the return weights in a map of key-value pairs: 
    // unsigned (layer indexes) to a vector of doubles (weights of the neurons)
    template<typename T>
    struct NeuralNetworkLayers {
        NeuralNetworkLayers() { } 
        NeuralNetworkLayers(const NeuralNetworkLayers<T>& layers) : m_score(layers.m_score), m_neurons(layers.m_neurons) { }

        bool operator==(NeuralNetworkLayers& right) const {
            if(right.m_score == this->m_score) {
                if(right.m_neurons == this->m_neurons) {
                    return true;
                }
            }
            return false;
        }

        NeuralNetworkLayers operator=(const NeuralNetworkLayers& right) {
            this->m_score = right.m_score;
            this->m_neurons = right.m_neurons;
            return *this;
        }

        // this value is not used initially when transferring the values
        // to the neural networks. It will be used in the history of 
        // weights to record how effective the weights were.
        double m_score = 0.0;
        std::map<unsigned, NeuralNetworkLayer<T>> m_neurons;
    };

    template<typename T>
    class NeuralNetworkWeights {
        NeuralNetworkWeights(const NeuralNetworkLayers<T>& layers) {
            for(unsigned i = 0; i < layers.m_neurons.size(); ++i) {
                // TODO
            }
        }

        std::map<unsigned, std::vector<double>> m_weights;
    };

    template<typename T>
    class NeuralNetwork {
        public:
        NeuralNetwork() { }
        NeuralNetwork(unsigned int num_of_layers, unsigned int neural_network_id) : m_neural_network_information(num_of_layers ,neural_network_id){ }
        NeuralNetwork(const NeuralNetworkLayers<T>& neural_network_layers, unsigned int num_of_layers, unsigned int neural_network_id) : m_neural_network_information(num_of_layers, neural_network_id), m_neural_network_layers(neural_network_layers) { }

        // mutator functions
        void set_neural_network_id(unsigned int neural_network_id) { m_neural_network_information.m_neural_network_id = neural_network_id; }
        NeuralNetworkLayerConstructionResult add_new_layer(unsigned int index_layer, const NeuralNetworkLayer<T>& new_layer_of_neurons);
        NeuralNetworkLayerConstructionResult overwrite_layer(unsigned int index_layer, const NeuralNetworkLayer<T>& replacement_layer_of_neurons);

        /*
            This function evaluates the neural network from the input layer to the output layer
            and returns the results of the neural network or an error if it didn't work.
        */
        NeuralNetworkReturnValue<T> evaluate(const std::vector<T>& input_values);
        /*------------------------------------------------------------------------------------------------
            This is a modification of the above function in which the values above a radix point
            are true and the values below the radix point are false. It runs the normal evaluate_double
            function below this and then evaluates the final value to a boolean based on the radix point.
        ------------------------------------------------------------------------------------------------*/
        NeuralNetworkReturnValue<T> evaluate(const std::vector<T>& input_values, double radix_point);

        private:
        /*-----------------------------------------------------------------------------------------
            These two functions are used to facilitate the usage of this neural network class as
            a representation of a feed-forward neural network in that the neurons connected in the
            neural network feed their values from the input layer to the output layer in one
            direction only.
        ------------------------------------------------------------------------------------------*/
        bool connecting_to_prev_layer(unsigned int current_layer_index);
        bool connecting_to_next_layer(unsigned int current_layer_index);
        
        bool operator==(NeuralNetwork& right) const {
            if(right.m_neural_network_information == this->m_neural_network_information) {
                if(right.m_neural_network_layers == this->m_neural_network_layers) {
                    return true;
                }
            }
            return false;
        }

        NeuralNetwork operator=(const NeuralNetwork& right) {
            if(right == *this) {
                return *this;
            }

            this->m_neural_network_information = right.m_neural_network_information;
            this->m_neural_network_layers = right.m_neural_network_layers;
            return *this;
        }

        /*--------------------------------------------------------
            This function is called before any evaluation is done.
        --------------------------------------------------------*/
        bool verify_connections();

        NeuralNetworkInformation m_neural_network_information;
        NeuralNetworkLayers<T> m_neural_network_layers;
    };

    template <typename T>
    using NeuralNetworkptr = std::shared_ptr<NeuralNetwork<T>>;
    template <typename T>
    using NeuralNetworks = std::vector<nsNeuralNetwork::NeuralNetworkptr<T>>;
}

#include "NeuralNetwork/NeuralNetwork.hpp"

#endif // NEURALNETWORK_HPP