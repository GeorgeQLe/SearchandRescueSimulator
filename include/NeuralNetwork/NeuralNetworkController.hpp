/*  Copyright 2018 George Le

*/
#ifndef NEURALNETWORKCONTROLLER_HPP
#define NEURALNETWORKCONTROLLER_HPP

#include "NeuralNetwork/NeuralNetwork.hpp"

namespace nsNeuralNetworkController {
    using NeuralNetworkptrs = std::vector<nsNeuralNetwork::NeuralNetworkptr>;

    class NeuralNetworkController {
        public:
        // singleton accessor function
        static NeuralNetworkController& get_instance() {
            static NeuralNetworkController instance;
            return instance;
        }

        // mutator function
        void set_neural_network(const nsNeuralNetwork::NeuralNetworkptr& new_network);

        std::vector<bool> evaluate_bool(const std::vector<bool>& input_values);
        std::vector<double> evaluate_double(const std::vector<double>& input_values);

        private:
        /*---------------------------------------------------------------------
            This class is a singleton and so to prevent the user from creating
            more than one of this class, we make the constructor private.
        ---------------------------------------------------------------------*/
        NeuralNetworkController() { }

        NeuralNetworkptrs m_neural_networks;
        
        unsigned int m_current_id;
    };
}

#endif