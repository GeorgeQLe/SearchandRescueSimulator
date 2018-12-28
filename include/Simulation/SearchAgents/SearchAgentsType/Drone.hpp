#ifndef DRONE_HPP
#define DRONE_HPP

#include <vector> // std::vector

#include "Environment/Support/Coord.hpp"
#include "Environment/Support/EnvironmentTypes/TileType.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "Simulation/SearchAgents/SearchAgents.hpp"

namespace nsDrone {
    using MoveTileList = std::vector<std::pair<bool, nsTileType::TileType>>;
    using SearchAdvantageTileList = std::vector<std::pair<bool, nsTileType::TileType>>;

    struct DroneInformation {
        DroneInformation(unsigned x, unsigned y) : m_coordinates(x, y) {}
        
        nsCoord::Coord m_coordinates;
        MoveTileList m_move_advantage_list = { { true, nsTileType::TileType::PLAINS },
                                                { true, nsTileType::TileType::TREE },
                                                { true, nsTileType::TileType::SWAMP },
                                                { true, nsTileType::TileType::HILL },
                                                { true, nsTileType::TileType::MOUNTAIN },
                                                { true, nsTileType::TileType::LAKE },
                                                { true, nsTileType::TileType::RIVER} };
        
        SearchAdvantageTileList m_search_advantage_list = { { true, nsTileType::TileType::PLAINS },
                                                            { false, nsTileType::TileType::TREE },
                                                            { false, nsTileType::TileType::SWAMP },
                                                            { true, nsTileType::TileType::HILL },
                                                            { true, nsTileType::TileType::MOUNTAIN },
                                                            { false, nsTileType::TileType::LAKE },
                                                            { false, nsTileType::TileType::RIVER} };
    };

    class Drone : public nsSearchAgent::SearchAgent {
        public:
        Drone(unsigned x, unsigned y) : m_information(x, y) {}

        virtual nsSearchAgent::enDirection move();
        virtual nsSearchAgent::enDirection search();

        private:
        DroneInformation m_information;
        nsNeuralNetwork::NeuralNetwork m_drone_controller;
    };
}

#endif