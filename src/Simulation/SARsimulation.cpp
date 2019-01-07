#include "GeneticProgrammer/GeneticProgrammer_NeuralNetwork.hpp"

#include "Simulation/SARsimulation.hpp"

void nsSARsimulation::SARsimulation::reset_simulation() {
    // resets the grid
    this->m_simulation_environment.reset_grid();
}

nsSARsimulation::SimulationSetupErrorInformation nsSARsimulation::SARsimulation::set_simulation_environment(unsigned x, unsigned y) {
    this->m_simulation_environment.set_environment(x, y);
    if(this->m_settings.check_simulation_settings()) {
        return { { true, enSimulationSetupErrorTypes::simulation_settings_error }, "There was a problem setting up the simulation."};
    }
    else {
        this->m_simulation_environment.generate_grid();
    }
    return {};
}

nsSARsimulation::SimulationErrorInformation nsSARsimulation::SARsimulation::set_simulation_settings(unsigned num_searchers, unsigned num_search_targets, unsigned frequency_false_positive) {
    if(num_searchers <= 0 || num_search_targets <= 0 || frequency_false_positive < 0) {
        return {};
    }
    else {
        this->m_settings = nsSARsimulation::SimulationSettings(num_searchers, num_search_targets, frequency_false_positive);
    }
    return {};
}

nsSARsimulation::SimulationResult nsSARsimulation::SARsimulation::run_simulation(unsigned num_of_turns) {
    if(!this->check_settings()) {
        return { { { true, enSimulationErrorTypes::simulation_settings_error }, "Before an attempt at a run of the simulation, there was error, either the environment settings or the simulation settings were not set." } };
    }
    // generates an instance of the environment for the simulation
    this->m_simulation_environment.generate_grid();

    // grabs an instance of the genetic programmer to create a random set of neural networks for the search agents
    // and in subsequent runs of the simulation, to make modification to the best neural networks of the previous
    // generation
    nsGeneticProgrammer_NeuralNetwork::GeneticProgrammer_NeuralNetwork f_instance = nsGeneticProgrammer_NeuralNetwork::GeneticProgrammer_NeuralNetwork::get_instance();

    for(unsigned i = 0; i < this->m_settings.m_num_searchers; ++i) {
        
    }

    // generates the various search agents for the simulation
    //this->m_list_of_agents.set_agents();

    unsigned last_turn = num_of_turns - 1;
    for(unsigned i = 0; i < num_of_turns; ++i) {
    //    this->m_simulation_environment.check_adjacent_tiles();
    }

    return nsSARsimulation::SimulationResult();
}

bool nsSARsimulation::SARsimulation::check_settings() {
    if(this->m_simulation_environment.check_environment_settings().first == false) {
        return false;
    }
    if(this->m_settings.check_simulation_settings() == false) {
        return false;
    }

    return true;
}