/*  Copyright 2018 George Le

*/
#ifndef GENETICALGORITHMBOOL_HPP
#define GENETICALGORITHMBOOL_HPP

#include <memory> // std::unique_ptr
#include <utility> // std::pair
#include <vector> // std::vector

namespace nsGeneticAlgorithm {

    using Individual = std::vector<bool>;
    using Population = std::vector<Individual>;
    using Scores = std::vector<double>;

    class GeneticAlgorithmBool {
        public:
        // singleton accessor function
        static GeneticAlgorithmBool& get_instance() {
            static GeneticAlgorithmBool instance;
            return instance;
        }
        // mutator functions
        void set_number_of_traits(unsigned int number_traits) { m_number_of_traits = number_traits; }
        void set_size_of_population(unsigned int size_population) { m_size_of_population = size_population; }
        void set_number_of_generations(unsigned int number_generations) { m_number_of_generations = number_generations; }
        void set_survival_rate(unsigned int survival_rate) { m_survival_rate = survival_rate; }
        void set_mutation_rate(unsigned int mutation_rate) { m_mutation_rate = mutation_rate; }

        /*--------------------------------------------------------------------
            User calls this function which will return the fittest individual
            that the genetic algorithm will generate. 
        --------------------------------------------------------------------*/
        Individual generate_expected_data();

        private:
        /*--------------------------------------------------------------------
            This class is a singleton and so to prevent the user from creating
            more than one of this class, we make the constructor private.
        --------------------------------------------------------------------*/
        GeneticAlgorithmBool() { }

        /*-----------------------------------------------------------------
            This function generates pseudo-random sequences for each of the
            members of the population. Because this genetic algorithm uses
            boolean values to model the traits of the individuals of the
            population.
        -----------------------------------------------------------------*/
        void generate_random_population();
        
        /*-----------------------------------------------------------------
            This function determines which members of the population is the
            fittest member of the generation which will survive and 
            reproduce for the next generation. 
        -----------------------------------------------------------------*/
        void fitness_function();

        /*-----------------------------------------------------------------
            This function determines which membersof the population is the
            fittest member of the last generation which will be returned 
            by the genetic algorithm and be parsed by a GA information
            table.
        -----------------------------------------------------------------*/
        Individual last_fitness_function(const Population& last_generation);
        
        /*-----------------------------------------------------------------
            Performs two point crossover on the parent organism strings.
        -----------------------------------------------------------------*/
        void two_point_crossover();

        /*--------------------------------------------------------------------
            Performs a bit string mutation on the child of the new generation.
        --------------------------------------------------------------------*/
        void bit_string_mutation(Individual& child);

        /*
            Member variables of the Genetic Algorithm
        */

        // this holds the current and the previous generations of the genetic algorithm
        std::pair<Population, Population> m_generations; // std::pair<std::vector<std::vector<bool>>, std::vector<std::vector<bool>>> 
                                                        // the first population is the current generation
                                                        // the second population is the next generation
        // temporarily holds the fittest population for crossover
        Population m_fittest_population; // std::vector<std::vector<bool>
        // this holds the scores for each of the individual's traits
        Scores m_method_scores;

        // useful variables for the genetic algorithm during runtime

        // number of traits that each individual will have
        unsigned int m_number_of_traits = 1; // default 1
        // population size
        unsigned int m_size_of_population = 10; // default 10
        // number of generations
        unsigned int m_number_of_generations = 10; // default 10
        // percantage survival rate (i.e. a value of 50 will be fifty percent survival rate)
        unsigned int m_survival_rate = 10; // default 10 (ten percent survival rate)
        // percentage mutation rate (i.e. a value of 1 will be one percent mutation rate)
        unsigned int m_mutation_rate = 1; // default 1

        // counter value
        unsigned int m_current_generation = 0; // starting generation is zero (incremented after generating first random generation)
    };
}

#endif