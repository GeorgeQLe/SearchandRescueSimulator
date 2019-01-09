/*  Copyright 2018 George Le

*/
#ifndef NEURALNETWORKCONTROLLER_HPP
#define NEURALNETWORKCONTROLLER_HPP

#include "NeuralNetwork/NeuralNetwork.hpp"

namespace nsNeuralNetworkController {
    template<typename T>
    class NeuralNetworkController {
        using NeuralNetworkptrs = std::vector<nsNeuralNetwork::NeuralNetworkptr<T>>;
        public:
        // singleton accessor function
        static NeuralNetworkController& get_instance() {
            static NeuralNetworkController instance;
            return instance;
        }

        // mutator function
        void set_neural_network(const nsNeuralNetwork::NeuralNetworkptr<T>& new_network);

        std::vector<T> evaluate(const std::vector<T>& input_values);

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

#include "NeuralNetwork/implementation/NeuralNetworkController.imp"

#endif // NEURALNETWORKCONTROLLER_HPP