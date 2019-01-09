#ifndef GENETICPROGRAMMER_NEURALNETWORK_HPP
#define GENETICPROGRAMMER_NEURALNETWORK_HPP

#include <map>
#include <memory>
#include <vector>

#include "GeneticAlgorithm/GeneticAlgorithm_NeuralNetwork.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"

namespace nsGeneticProgrammer_NeuralNetwork {

    enum class GeneticProgrammerErrorTypes {
        NO_ERROR,
        COUNT
    };
    using GeneticProgrammerError = std::pair<bool, GeneticProgrammerErrorTypes>;

    struct GeneticProgrammerErrorInformation {
        GeneticProgrammerErrorInformation() { }
        GeneticProgrammerErrorInformation(GeneticProgrammerError error, const std::string& error_message) : m_error(error), m_error_message(error_message) { }

        GeneticProgrammerError m_error = { false, GeneticProgrammerErrorTypes::NO_ERROR };
        std::string m_error_message = "GeneticProgrammer: NO ERROR YET";
    };

    struct GeneticProgrammerSettings {
        GeneticProgrammerSettings() { }
        GeneticProgrammerSettings(unsigned size_population, unsigned number_generations, unsigned survival_rate, unsigned mutation_rate) 
        : m_size_of_population(size_population), m_number_of_generations(number_generations), m_survival_rate(survival_rate), m_mutation_rate(mutation_rate) { }

        // useful variables for the genetic algorithm during runtime that the genetic programmer can assign

        // population size
        unsigned m_size_of_population = 10; // default 10
        // number of generations
        unsigned m_number_of_generations = 10; // default 10
        // percantage survival rate (i.e. a value of 50 will be fifty percent survival rate)
        unsigned m_survival_rate = 10; // default 10 (ten percent survival rate)
        // percentage mutation rate (i.e. a value of 1 will be one percent mutation rate)
        unsigned m_mutation_rate = 1; // default 1
    };

    
    template <typename T>
    class GeneticProgrammer_NeuralNetwork {
        using RecordNeuralNetworkWeights = std::vector<nsNeuralNetwork::NeuralNetworkLayers<T>>;

        public:
        static GeneticProgrammer_NeuralNetwork& get_instance() {
            static GeneticProgrammer_NeuralNetwork instance;
            return instance;
        }
        /*----------------------------------------------------------------------
            This function generates pseudo-random weights for the individual
            neural networks. This function will be used by the GeneticProgrammer
            to generate the first initial population of neural networks.
        ----------------------------------------------------------------------*/
        GeneticProgrammerErrorInformation generate_neural_networks(nsNeuralNetwork::NeuralNetworks<T>& new_neural_nets);

        GeneticProgrammerErrorInformation generate_from_existing_neural_networks(nsNeuralNetwork::NeuralNetworks<T>& neural_nets_to_be_modified);

        private:
        /*--------------------------------------------------------------------
            This class is a singleton and so to prevent the user from creating
            more than one of this class, we make the constructor private.
        --------------------------------------------------------------------*/
        GeneticProgrammer_NeuralNetwork() { }

        /*----------------------------------------------------
            This function will randomly generate weights for
            test neural network and record the random weights
            into the m_record_weights.
        ----------------------------------------------------*/
        nsNeuralNetwork::NeuralNetworkLayers<T> generate_layers();

        // contains all the previous weight combinations and their scores
        RecordNeuralNetworkWeights m_record_weights;
    };
}

#endif // GENETICPROGRAMMER_NEURALNETWORK_HPP