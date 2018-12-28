#include <iostream>
#include <random>

#include "GeneticAlgorithm/Utilities/GeneticAlgorithmUtilities.hpp"

int nsGeneticAlgorithmUtilities::return_rand_index(int smallest_index, int greatest_index) {
    int random_number = -1;
    
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dist(smallest_index, greatest_index);
    random_number = dist(gen); 

    return random_number;
}

bool nsGeneticAlgorithmUtilities::return_random_bool() {
    int random_number = nsGeneticAlgorithmUtilities::return_rand_index(0, 1);

    if(random_number) {
        return true;
    }
    return false;
}

bool nsGeneticAlgorithmUtilities::percentage_chance(unsigned int percentage_chance) {
    unsigned int num = nsGeneticAlgorithmUtilities::return_rand_index(1, 100);

    if(num <= percentage_chance) {
        return true;
    }
    return false;
}

bool nsGeneticAlgorithmUtilities::percentage_chance(unsigned int percentage_chance) {
    unsigned int num = nsGeneticAlgorithmUtilities::return_rand_index(1, 100);

    if(num <= percentage_chance) {
        return true;
    }
    return false;
}

int nsGeneticAlgorithmUtilities::partition(std::vector<double>& list, unsigned int left, unsigned int right) {
    // set partition equal to the right
    int f_partition = left;
    // create a temporary reference to the element in the vector at the left
    double f_temp = list.at(left);
    
    // compare from the left hand element to the right hand element, the right
    // hand element being the partition
    for(unsigned int i = left + 1; i < right; ++i) {
        // generic function in condition for what you want to compare in the vectors
        // if the element in the vector at the left+1 position is (comp definition)
        // to the element at the left position then execute within this
        // (assume less than for smallest to largest, greater than for largest to smallest)
        if(list.at(i) <= f_temp) {
            // increment the partition
            f_partition++;
            // swap the elements at the partition with the element at the 
            // i'th position
            std::swap(list.at(f_partition), list.at(i));
        }
    }
    // swap the partition with the left hand side
    std::swap(list.at(f_partition), list.at(left));
    return f_partition;
}

void nsGeneticAlgorithmUtilities::quicksort(std::vector<double>& list, unsigned int left, unsigned int right) {
    int f_partition;
    
    // ensure that left is less than right as it should
    if(left < right) {
        // get the partition for the quick sort and sort from the left to the right
        f_partition = nsGeneticAlgorithmUtilities::partition(list, left, right);
        // recursively call quicksort with the new partition being the right
        quicksort(list , left, f_partition);  
        // recursively call quicksort with the new partition incremented by 1 being
        // the left hand side
        quicksort(list, f_partition + 1, right);
    }
}

void nsGeneticAlgorithmUtilities::swap_range(std::vector<bool>& child1, std::vector<bool>& child2, nsGeneticAlgorithmUtilities::Swap_points start_and_end) {
    if(child1.size() == child2.size()) {
        for(unsigned int i = start_and_end.start_point; i < start_and_end.end_point; ++i) {
            std::swap(child1.at(i), child2.at(i));
        }
    }
    else {
        std::cout << "Children dont have the same amount of traits\n";
    }
}