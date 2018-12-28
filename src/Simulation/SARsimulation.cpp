#include "Simulation/SARsimulation.hpp"

void nsSARsimulation::SARsimulation::reset_simulation() {
    this->m_simulation_environment.reset_grid();
}

nsSARsimulation::SimulationSetupErrorInformation nsSARsimulation::SARsimulation::set_simulation_environment(unsigned x, unsigned y) {
    this->m_simulation_environment.set_environment(x, y);
    if(this->m_settings.check_simulation_settings()) {
        return { { true, enSimulationSetupErrorTypes::SIMULATION_SETUP_ERROR }, "There was a problem setting up the simulation."};
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
        return {};
    }

    this->m_simulation_environment.generate_grid();
    unsigned last_turn = num_of_turns - 1;
    for(unsigned i = 0; i < num_of_turns; ++i) {
        if(i == last_turn) {
            this->m_simulation_environment.resolve_final_turn();
        }
        else {
            this->m_simulation_environment.resolve_turn();
        }
    }

    return nsSARsimulation::SimulationResult();
}