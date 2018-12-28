/*  Copyright 2018 George Le

*/
#ifndef SARSIMULATION_HPP
#define SARSIMULATION_HPP

#include <memory> // std::shared_ptr
#include <utility> // std::pair
#include <string> // std::string
#include <vector> // std::vector

#include "Environment/Environment.hpp"
#include "Simulation/SearchAgents/SearchAgents.hpp"

namespace nsSARsimulation {
    enum class enSimulationErrorTypes {
        NO_ERROR,
        ENVIRONMENT_SETTINGS_ERROR,
        SIMULATION_SETTINGS_ERROR,
        COUNT
    };
    using SimulationError = std::pair<bool, enSimulationErrorTypes>;

    struct SimulationErrorInformation {
        SimulationErrorInformation() { }
        SimulationErrorInformation(const SimulationError& error, const std::string& error_message) {
            if(error.first) {
                m_simulation_error = error;
                m_error_message = error_message;
            }
        }

        SimulationError m_simulation_error = { false, enSimulationErrorTypes::NO_ERROR };
        std::string m_error_message = "NO ERROR YET";
    };

    enum class enSimulationSetupErrorTypes {
        NO_ERROR,
        SIMULATION_SETUP_ERROR
    };
    using SimulationSetupError = std::pair<bool, enSimulationSetupErrorTypes>;
    using SimulationTargets = std::vector<std::pair<unsigned, unsigned>>;

    struct SimulationSetupErrorInformation {
        SimulationSetupErrorInformation() { }
        SimulationSetupErrorInformation(const SimulationSetupError& error, const std::string& error_message) {
            if(error.first) {
                m_simulation_error = error;
                m_error_message = error_message;
            }
        }

        SimulationSetupError m_simulation_error = { false, enSimulationSetupErrorTypes::NO_ERROR };
        std::string m_error_message = "NO ERROR YET";
    };

    struct SimulationResult {
        SimulationResult() { }
        SimulationResult(bool success, unsigned number_moves, unsigned number_false_pos_found, unsigned number_false_pos_disregarded)
        : m_success(success), m_number_moves(number_moves), m_number_false_pos_found(number_false_pos_found), m_number_false_pos_disregarded(number_false_pos_disregarded) {}

        bool m_success = false;
        unsigned m_number_moves = 0;
        unsigned m_number_false_pos_found = 0;
        unsigned m_number_false_pos_disregarded = 0;
        
        SimulationTargets m_targets;
    };

    using SimulationSearchAgentFleet = std::vector<std::shared_ptr<nsSearchAgent::SearchAgent>>;
    class SimulationSearchAgents {
        public:
        SimulationSearchAgents(unsigned number_of_agents) {
            for(unsigned i = 0; i < number_of_agents; ++i) {
                std::shared_ptr<nsSearchAgent::SearchAgent> temp_agents;
                m_agents.push_back(temp_agents);
            }
        }

        // accessor functions
        SimulationSearchAgentFleet get_agents() const { return m_agents; }
        
        // mutator functions
        void set_agents(const SimulationSearchAgentFleet& agents) {
            for(unsigned i = 0; i < this->m_agents.size(); ++i) {
                m_agents.at(i) = agents.at(i);
            }
            if(m_agents.size() < agents.size()) {
                for(unsigned i = agents.size() - m_agents.size(); i < agents.size(); ++i) {
                    m_agents.push_back(agents.at(i));
                }
            }
        }

        private:
        SimulationSearchAgentFleet m_agents;
    };

    class SimulationSettings {
        public:
        SimulationSettings() { }
        SimulationSettings(unsigned num_of_searchers, unsigned num_of_targets, unsigned frequency_false_pos)
        : m_setup(true), m_num_searchers(num_of_searchers), m_num_search_targets(num_of_targets), m_frequency_false_positive(frequency_false_pos) {}

        bool check_simulation_settings() const { return m_setup; }

        private:
        bool m_setup = false;
        unsigned m_num_searchers = 0;
        unsigned m_num_search_targets = 0;
        unsigned m_frequency_false_positive = 0;
    };

    class SARsimulation {
        public:
        static SARsimulation& get_instance() {
            static SARsimulation instance;
            return instance;
        }

        /*--------------------------------------------------------------------------------
            This function runs one iteration of the simulation and returns the results of
            the simulation which includes the number of moves the search agents took,
            the amount of false positives the search agents got duped by, the number of
            false positives the search agents disregarded, and most importantly the 
            locations of the found targets and if the agents found all of the targets.
        --------------------------------------------------------------------------------*/
        SimulationResult run_simulation(unsigned num_of_turns);
        
        /*--------------------------------------------------------------------------------.
            This function is nearly the same as the above function (and will actually call)
            the above function. It bundles the set_simulation_environment and set_simulat-
            ion_settings functions with the standard run_simulation function.
        ---------------------------------------------------------------------------------*/
        SimulationResult run_simulation(unsigned max_x, unsigned max_y, unsigned num_of_searchers, unsigned num_of_targets, unsigned frequency_false_pos);

        void reset_simulation();
        
        // mutator functions
        SimulationSetupErrorInformation set_simulation_environment(unsigned max_x, unsigned max_y);
        SimulationErrorInformation set_simulation_settings(unsigned num_of_searchers, unsigned num_of_targets, unsigned frequency_false_pos);

        private:
        SARsimulation() { }

        bool check_settings();

        nsEnvironment::Environment m_simulation_environment;
        SimulationResult m_results;  
        SimulationSettings m_settings;
    };
}

#endif