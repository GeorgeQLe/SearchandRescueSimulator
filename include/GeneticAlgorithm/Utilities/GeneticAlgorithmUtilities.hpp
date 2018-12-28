#ifndef GENETICALGORITHMUTILITIES_HPP
#define GENETICALGORITHMUTILITIES_HPP

#include <utility>
#include <vector>

// utilty functions for use with the genetic algorithm only
namespace nsGeneticAlgorithmUtilities {
    int return_rand_index(int smallest_index, int greatest_index);

    bool return_random_bool();

    bool percentage_chance(unsigned percentage_chance);
    
    int partition(std::vector<double>& list, unsigned left, unsigned right);

    void quicksort(std::vector<double>& list, unsigned left, unsigned right);

    void quicksort(std::vector<std::pair<unsigned, double>> list, unsigned left, unsigned right);

    struct Swap_points {
        Swap_points(unsigned new_start_point, unsigned new_end_point) : start_point(new_start_point), end_point(new_end_point) { }

        unsigned start_point;
        unsigned end_point;
    };

    void swap_range(std::vector<bool>& child1, std::vector<bool>& child2, Swap_points start_and_end);
    
}

#endif