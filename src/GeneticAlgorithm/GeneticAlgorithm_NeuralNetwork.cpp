#include "GeneticAlgorithm/GeneticAlgorithm_NeuralNetwork.hpp"
#include "GeneticAlgorithm/Utilities/GeneticAlgorithmUtilities.hpp"

nsGeneticAlgorithm_NeuralNetwork::Individual nsGeneticAlgorithm_NeuralNetwork::GeneticAlgorithm_NeuralNetwork::generate_fittest_individual(const Population& test_population, const Scores& scores_of_neural_networks) {
    Individual fittest_individual;

    for (unsigned index_generation = 1; index_generation < this->m_population_information.m_number_of_generations; ++index_generation) {
        fitness_function(scores_of_neural_networks);
        two_point_crossover();
        this->m_population.m_generations.first = this->m_population.m_generations.second;
    }
    fittest_individual = last_fitness_function(this->m_population.m_generations.first, scores_of_neural_networks);
    return fittest_individual;
}

void nsGeneticAlgorithm_NeuralNetwork::GeneticAlgorithm_NeuralNetwork::fitness_function(const Scores& scores) {
    // sorts a temporary container 
    Scores sorted_scores = scores;

    // sorts the scores from greatest to least
    nsGeneticAlgorithmUtilities::quicksort(sorted_scores, 0, sorted_scores.size());

    // calculates the cutoff score for individuals
    double radix = sorted_scores.at(scores.size() / nsGeneticAlgorithmUtilities::percentage_chance(this->m_population_information.m_survival_rate)).second;
    // clears the fittest population if it has been used before
    if(this->m_population.m_fittest_population.size() > 0) {
        this->m_population.m_fittest_population.clear();
    }
    // for each of the scores
    for(unsigned int index = 0; index < scores.size(); ++index) {
        // if the scores is greater than or equal to the cuttoff score
        // then add it to the fittest population for crossover
        if(scores.at(index).second >= radix) {
            this->m_population.m_fittest_population.push_back(this->m_population.m_generations.first.at(index));
        }
    }
}

nsGeneticAlgorithm_NeuralNetwork::Individual nsGeneticAlgorithm_NeuralNetwork::GeneticAlgorithm_NeuralNetwork::last_fitness_function(const Population& last_generation, const Scores& scores) {
    // initializes a vector of doubles with 0.0 for each of the
    // member of the population
    Scores average_scores = scores;

    // then find the fittest individual
    double highest_score = 0.0, highest_index = 0;
    for(unsigned int i = 0; i < average_scores.size(); ++i) {
        if(average_scores.at(i).second >= highest_score) {
            highest_score = average_scores.at(i).second;
            highest_index = i;
        }
    }
    // then return that fittest individual
    return last_generation.at(highest_index);
}

void nsGeneticAlgorithm_NeuralNetwork::GeneticAlgorithm_NeuralNetwork::two_point_crossover() {
    Individual child1, child2; // std::vector<bool>
    int index_parent1 = -1, index_parent2 = -1;

    // clear the next generation if it has been used
    if(this->m_population.m_generations.second.size() > 0) {
        this->m_population.m_generations.second.clear();
    }

    // push all the fittest population into the next generation
    for(unsigned int i = 0; i < this->m_population.m_fittest_population.size(); ++i) {
        this->m_population.m_generations.second.push_back(this->m_population.m_fittest_population.at(i));
    }

    // select two at random of the fittest population to reproduce
    // a new individual of the next generation and there is a coin
    // flip to see if the individual has a mutation. Add the new 
    // individual to the next generation.
    while(this->m_population.m_generations.second.size() < this->m_population_information.m_size_of_population) {
        // generates where the start and the end points of the uniform crossover
        unsigned int index_start_flip = nsGeneticAlgorithmUtilities::return_rand_index(0, this->m_population. - 2);
        unsigned int index_end_flip = nsGeneticAlgorithmUtilities::return_rand_index(index_start_flip + 1, m_number_of_traits - 1);
        
        // randomly selects two parents
        index_parent1 = nsGeneticAlgorithmUtilities::return_rand_index(0, this->m_population.m_fittest_population.size() - 1);
        index_parent2 = nsGeneticAlgorithmUtilities::return_rand_index(0, this->m_population.m_fittest_population.size() - 1);
        
        // creates two children from the two parents
        child1 = this->m_population.m_fittest_population.at(index_parent1);
        child2 = this->m_population.m_fittest_population.at(index_parent2);

        // applies the crossover to the children at the randomly generated start and end points
        nsGeneticAlgorithmUtilities::swap_range(child1, child2, { index_start_flip, index_end_flip });

        // coin flip to see if the child recieves a mutation
        if(nsGeneticAlgorithmUtilities::percentage_chance(this->m_population_information.m_mutation_rate)) {
            bit_string_mutation(child1);
        }
        if(nsGeneticAlgorithmUtilities::percentage_chance(this->m_population_information.m_mutation_rate)) {
            bit_string_mutation(child2);
        }
        // adds the child to the new generation
        this->m_population.m_generations.second.push_back(child1);
        // checks if the child can join the new generation or if its addition will
        // overpopulate the next generation
        if(this->m_population.m_generations.second.size() < this->m_population_information.m_size_of_population) {
            // if there is still space in the next generation, the child is added
            this->m_population.m_generations.second.push_back(child2);
        }
    }
}

void nsGeneticAlgorithm_NeuralNetwork::GeneticAlgorithm_NeuralNetwork::bit_string_mutation(nsGeneticAlgorithm_NeuralNetwork::Individual& child) {

}