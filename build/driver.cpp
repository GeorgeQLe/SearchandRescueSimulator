/*  Copyright 2018 George Le

    This file defines the program's main function which controls the various components of the simulation.
*/
#include <iostream>
#include "NeuralNetwork/Neuron.hpp"
#include "GeneticProgrammer/GeneticProgrammer_NeuralNetwork.hpp"
#include "Simulation/SARsimulation.hpp"

int main() {
    nsSARsimulation::SARsimulation simulation = nsSARsimulation::SARsimulation::get_instance();

    nsSARsimulation::SimulationResult results = simulation.run_simulation(50);
    return 0;
}