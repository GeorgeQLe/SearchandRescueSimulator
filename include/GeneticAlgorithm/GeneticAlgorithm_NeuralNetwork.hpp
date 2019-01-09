#ifndef GENETICALGORITHM_NEURALNETWORK_HPP
#define GENETICALGORITHM_NEURALNETWORK_HPP

#include <map>
#include <utility>
#include <vector>

#include "NeuralNetwork/NeuralNetwork.hpp"

namespace nsGeneticAlgorithm_NeuralNetwork {

    template <typename T>
    using Individual = nsNeuralNetwork::NeuralNetwork<T>;
    template <typename T>
    using Population = std::vector<Individual<T>>;
    using Scores = std::vector<std::pair<unsigned, double>>;

    template <typename T>
    struct GeneticAlgorithmPopulationContainer {
        GeneticAlgorithmPopulationContainer() { }

        // this holds the current and the previous generations of the genetic algorithm
        std::pair<Population<T>, Population<T>> m_generations;
        // temporarily holds the fittest population for crossover
        Population<T> m_fittest_population;
    };

    struct GeneticAlgorithmPopulationInformation {
        GeneticAlgorithmPopulationInformation() { }
        GeneticAlgorithmPopulationInformation(unsigned size_population, unsigned number_generations, unsigned survival_rate, unsigned mutation_rate) 
        : m_size_of_population(size_population), m_number_of_generations(number_generations), m_survival_rate(survival_rate), m_mutation_rate(mutation_rate) { }

        // useful variables for the genetic algorithm during runtime

        unsigned m_current_generation = 0;
        // population size
        unsigned m_size_of_population = 10; // default 10
        // number of generations
        unsigned m_number_of_generations = 10; // default 10
        // percantage survival rate (i.e. a value of 50 will be fifty percent survival rate)
        unsigned m_survival_rate = 10; // default 10 (ten percent survival rate)
        // percentage mutation rate (i.e. a value of 1 will be one percent mutation rate)
        unsigned m_mutation_rate = 1; // default 1
    };

    template<typename T>
    class GeneticAlgorithm_NeuralNetwork {
        public:
        // singleton accessor function
        static GeneticAlgorithm_NeuralNetwork& get_instance() {
            static GeneticAlgorithm_NeuralNetwork instance;
            return instance;
        }

        // mutator functions
        void set_mutation_rate(unsigned mutation_rate) { m_population_information.m_mutation_rate = mutation_rate; }
        void set_number_of_generations(unsigned number_generations) { m_population_information.m_number_of_generations = number_generations; }
        void set_size_of_population(unsigned size_population) { m_population_information.m_size_of_population = size_population; }
        void set_survival_rate(unsigned survival_rate) { m_population_information.m_survival_rate = survival_rate; }

        /*--------------------------------------------------------------------
            User calls this function which will return the fittest individual
            that the genetic algorithm will generate. 
        --------------------------------------------------------------------*/
        Individual<T> generate_fittest_individual(const Population<T>& test_population, const Scores& scores_of_neural_networks);

        private:
        /*--------------------------------------------------------------------
            This class is a singleton and so to prevent the user from creating
            more than one of this class, we make the constructor private.
        --------------------------------------------------------------------*/
        GeneticAlgorithm_NeuralNetwork() {}

        /*-----------------------------------------------------------------
            This function determines which members of the population is the
            fittest member of the generation which will survive and 
            reproduce for the next generation. 
        -----------------------------------------------------------------*/
        void fitness_function(const Scores& scores);

        /*-----------------------------------------------------------------
            This function determines which member of the population is the
            fittest member of the last generation which will be returned 
            by the genetic algorithm and be parsed by a GA information
            table.
        -----------------------------------------------------------------*/
        Individual<T> last_fitness_function(const Population<T>& last_generation, const Scores& scores);

        /*-----------------------------------------------------------------
            Performs two point crossover on the parent organism strings.
        -----------------------------------------------------------------*/
        void two_point_crossover();

        /*--------------------------------------------------------------------
            Performs a bit string mutation on the child of the new generation.
        --------------------------------------------------------------------*/
        void bit_string_mutation(Individual<T>& child);

        GeneticAlgorithmPopulationContainer<T> m_population;
        GeneticAlgorithmPopulationInformation m_population_information;
    };
}

#include "GeneticAlgorithm/implementation/GeneticAlgorithm_NeuralNetwork.imp"

#endif