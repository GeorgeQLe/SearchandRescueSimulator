#ifndef GENETICPROGRAMMER_NEURALNETWORK_HPP
#define GENETICPROGRAMMER_NEURALNETWORK_HPP

#include <map>
#include <memory>
#include <vector>

#include "GeneticAlgorithm/GeneticAlgorithm_NeuralNetwork.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"

namespace nsGeneticProgramer_NeuralNetwork {

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

    struct NeuralNetworkWeights {
        NeuralNetworkWeights() {
            m_weights = std::shared_ptr<std::map<unsigned, std::vector<double>>>(new std::map<unsigned, std::vector<double>>);
        }
        double score = 0.0;
        std::shared_ptr<std::map<unsigned, std::vector<double>>> m_weights = nullptr;
    };
    using RecordNeuralNetworkWeights = std::vector<NeuralNetworkWeights>;

    class GeneticProgrammer_NeuralNetwork {
        public:
        static GeneticProgrammer_NeuralNetwork& get_instance() {
            static GeneticProgrammer_NeuralNetwork instance;
            return instance;
        }

        /*-----------------------------------------------------------------------------
            This function will test the generated weights in a test neural network and 
            return the best neural network after a run of testing.
        -----------------------------------------------------------------------------*/
        nsNeuralNetwork::NeuralNetwork genetic_algorithm_generate_best_neural_network();

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
        NeuralNetworkWeights generate_weights();

        /*----------------------------------------------------------------------
            This function generates pseudo-random weights for the individual
            neural networks. This function will be used by the GeneticProgrammer
            to generate the first initial population of neural networks.
        ----------------------------------------------------------------------*/
        std::vector<nsNeuralNetwork::NeuralNetwork> generate_random_population();

        // contains all the previous weight combinations and their scores
        RecordNeuralNetworkWeights m_record_weights;
    };
}

#endif