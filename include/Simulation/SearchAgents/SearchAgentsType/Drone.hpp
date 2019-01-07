#ifndef DRONE_HPP
#define DRONE_HPP

#include <vector> // std::vector

#include "Environment/Support/Coord.hpp"
#include "Environment/Environment.hpp"
#include "Environment/Support/EnvironmentTypes/TerrainType.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "Simulation/SearchAgents/SearchAgents.hpp"

namespace nsDrone {
    using MoveTileList = std::vector<std::pair<bool, nsTerrainType::TerrainType>>;
    using SearchAdvantageTileList = std::vector<std::pair<bool, nsTerrainType::TerrainType>>;

    struct DroneInformation {
        DroneInformation(const nsCoord::Coord& coordinate) : m_coordinate(coordinate) {}
        
        nsCoord::Coord m_coordinate;
        MoveTileList m_move_advantage_list = { { true, nsTerrainType::TerrainType::plains },
                                                { true, nsTerrainType::TerrainType::forest },
                                                { true, nsTerrainType::TerrainType::swamp },
                                                { true, nsTerrainType::TerrainType::hill },
                                                { true, nsTerrainType::TerrainType::mountain },
                                                { true, nsTerrainType::TerrainType::lake },
                                                { true, nsTerrainType::TerrainType::river } };
        
        SearchAdvantageTileList m_search_advantage_list = { { true, nsTerrainType::TerrainType::plains },
                                                            { false, nsTerrainType::TerrainType::forest },
                                                            { false, nsTerrainType::TerrainType::swamp },
                                                            { true, nsTerrainType::TerrainType::hill },
                                                            { true, nsTerrainType::TerrainType::mountain },
                                                            { false, nsTerrainType::TerrainType::lake },
                                                            { false, nsTerrainType::TerrainType::river } };
    };

    class DroneActions : public nsSearchAgent::SearchAgentAction {
        public:
        virtual nsSearchAgent::SearchAgentActionErrorInformation execute() { }
    };
    using DroneActionsPtr = std::shared_ptr<DroneActions>;
    using ListofDroneActions = std::vector<DroneActionsPtr>;

    class Drone : public nsSearchAgent::SearchAgent {
        public:
        Drone(const nsCoord::Coord& coordinate) : m_information(coordinate) {}

        bool verify_actions() {
            if(m_actions.size() == 0) {
                return false;
            }
            else {
                for(auto it = m_actions.begin(); it != m_actions.end(); ++it) {
                    if(*it == nullptr) {
                        return false;
                    }
                }
            }
            return true;
        }

        nsSearchAgent::enDirection move(const nsEnvironment::AdjacentTiles& current_adjacent_tile);
        bool search();

        private:
        ListofDroneActions m_actions;
        DroneInformation m_information;
        nsNeuralNetwork::NeuralNetworkptr m_drone_controller = nullptr;
    };
}

#endif // DRONE_HPP