/*  Copyright 2018 George Le

*/
#include <random>

#include "Environment/Environment.hpp"
#include "Environment/Support/Tiles/Empty.hpp"
#include "Environment/Support/Tiles/Falsepos.hpp"
#include "Environment/Support/Tiles/Target.hpp"

nsEnvironment::GridTile nsEnvironment::AdjacentTiles::generate_random_grid_tile(const nsEnvironment::EnvironmentGrid& sim_grid, const nsCoord::Coord& current_coords) {
    // grabs all of the adjacent tiles (if there are any) to the
    // current coordinate
    this->set_adjacent_tile_types(sim_grid, current_coords);

    // generates a random number between 1-100
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dist(1, 100);
    int random_number = dist(gen); 

    // if the random number is one, then make the current tile a target
    if(random_number == 1) {
        return nsEnvironment::GridTile(new nsTarget::Target(current_coords, this->count_tile_probabilities()));
    }
    // if the random number is between 2 and 10, then make the current tile a false positive
    else if(random_number > 1 && random_number <= 10) {
        return nsEnvironment::GridTile(new nsFalsePositive::FalsePositive(current_coords, this->count_tile_probabilities()));
    }
    // if the random number is greater than 10 then make it empty
    else {
        return nsEnvironment::GridTile(new nsEmpty::Empty(current_coords, this->count_tile_probabilities()));
    }

    return nullptr;
}

nsTerrainType::TerrainType nsEnvironment::AdjacentTiles::count_tile_probabilities() {
    // totals up the various probabilities of the terrains
    nsTerrainType::TileProbability f_return_probabilities;
    for(unsigned i = 0; i < static_cast<unsigned>(nsTerrainType::TerrainType::count); ++i) {
        if(this->m_tiles[i] == nullptr) {
            f_return_probabilities.m_probabilities[nsTerrainType::TerrainType::notrelevant] += 0;
        }
        else if(this->m_tiles[i]->get_terrain_type() == nsTerrainType::TerrainType::home) {
            f_return_probabilities.m_probabilities[nsTerrainType::TerrainType::home] += 0;
        }
        else if(this->m_tiles[i]->get_terrain_type() == nsTerrainType::TerrainType::plains) {
            f_return_probabilities.m_probabilities[nsTerrainType::TerrainType::plains] += 12.5;
        }
        else if(this->m_tiles[i]->get_terrain_type() == nsTerrainType::TerrainType::forest) {
            f_return_probabilities.m_probabilities[nsTerrainType::TerrainType::forest] += 12.5;
        }
        else if(this->m_tiles[i]->get_terrain_type() == nsTerrainType::TerrainType::swamp) {
            f_return_probabilities.m_probabilities[nsTerrainType::TerrainType::swamp] += 12.5;
        }
        else if(this->m_tiles[i]->get_terrain_type() == nsTerrainType::TerrainType::hill) {
            f_return_probabilities.m_probabilities[nsTerrainType::TerrainType::hill] += 12.5;
        }
        else if(this->m_tiles[i]->get_terrain_type() == nsTerrainType::TerrainType::mountain) {
            f_return_probabilities.m_probabilities[nsTerrainType::TerrainType::mountain] += 12.5;
        }
        else if(this->m_tiles[i]->get_terrain_type() == nsTerrainType::TerrainType::lake) {
            f_return_probabilities.m_probabilities[nsTerrainType::TerrainType::lake] += 12.5;
        }
        else if(this->m_tiles[i]->get_terrain_type() == nsTerrainType::TerrainType::river) {
            f_return_probabilities.m_probabilities[nsTerrainType::TerrainType::river] += 12.5;
        }
    }

    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dist(0, 100);
    int random_number = dist(gen); 

    return f_return_probabilities.resolve_probabilities(random_number);
}

void nsEnvironment::AdjacentTiles::set_adjacent_tile_types(const nsEnvironment::EnvironmentGrid& sim_grid, const nsCoord::Coord& current_coords) {
    
    // searches on the grid to see if there is a tile to the top left of the current grid square
    auto check_grid = sim_grid->find(current_coords.m_x - 1);
    if(check_grid != sim_grid->end()) {
        if(sim_grid->at(current_coords.m_x - 1).size() < current_coords.m_y - 1) {
            this->m_tiles[0] = sim_grid->at(current_coords.m_x - 1).at(current_coords.m_y - 1);
        }
    }
    // searches on the grid to see if there is a tile to the top middle of the current grid square
    check_grid = sim_grid->find(current_coords.m_x - 1);
    if(check_grid != sim_grid->end()) {
        if(sim_grid->at(current_coords.m_x).size() < current_coords.m_y) {
            this->m_tiles[1] = sim_grid->at(current_coords.m_x - 1).at(current_coords.m_y);
        }
    }
    // searches on the grid to see if there is a tile to the top right of the current grid square
    check_grid = sim_grid->find(current_coords.m_x - 1);
    if(check_grid != sim_grid->end()) {
        if(sim_grid->at(current_coords.m_x - 1).size() < current_coords.m_y + 1) {
            this->m_tiles[2] = sim_grid->at(current_coords.m_x - 1).at(current_coords.m_y + 1);
        }
    }
    // searches on the grid to see if there is a tile to the right middle of the current grid square
    check_grid = sim_grid->find(current_coords.m_x);
    if(check_grid != sim_grid->end()) {
        if(sim_grid->at(current_coords.m_x).size() < current_coords.m_y + 1) {
            this->m_tiles[3] = sim_grid->at(current_coords.m_x).at(current_coords.m_y + 1);
        }
    }
    // searches on the grid to see if there is a tile to the bottom right of the current grid square
    check_grid = sim_grid->find(current_coords.m_x + 1);
    if(check_grid != sim_grid->end()) {
        if(sim_grid->at(current_coords.m_x + 1).size() < current_coords.m_y + 1) {
            this->m_tiles[4] = sim_grid->at(current_coords.m_x + 1).at(current_coords.m_y + 1);
        }
    }
    // searches on the grid to see if there is a tile to the bot middle of the current grid square
    check_grid = sim_grid->find(current_coords.m_x + 1);
    if(check_grid != sim_grid->end()) {
        if(sim_grid->at(current_coords.m_x + 1).size() < current_coords.m_y) {
            this->m_tiles[5] = sim_grid->at(current_coords.m_x + 1).at(current_coords.m_y);
        }
    }
    // searches on the grid to see if there is a tile to the bot left of the current grid square
    check_grid = sim_grid->find(current_coords.m_x + 1);
    if(check_grid != sim_grid->end()) {
        if(sim_grid->at(current_coords.m_x + 1).size() < current_coords.m_y - 1) {
            this->m_tiles[6] = sim_grid->at(current_coords.m_x + 1).at(current_coords.m_y - 1);
        }
    }
    // searches on the grid to see if there is a tile to the left middle of the current grid square
    check_grid = sim_grid->find(current_coords.m_x);
    if(check_grid != sim_grid->end()) {
        if(sim_grid->at(current_coords.m_x).size() < current_coords.m_y - 1) {
            this->m_tiles[7] = sim_grid->at(current_coords.m_x).at(current_coords.m_y - 1);
        }
    }
}

nsEnvironment::GenerateGridError nsEnvironment::Environment::check_environment_settings() {
    if(this->m_settings.m_max_x == 0) {
        return { true, enGenerateGridErrorTypes::MAX_X_VALUE_NOT_SET };
    }
    else if(this->m_settings.m_max_y == 0) {
        return { true, enGenerateGridErrorTypes::MAX_Y_VALUE_NOT_SET };
    } 
    // else if(this->m_settings.m_area_type == nsAreaType::AreaType::VOID) {
    //     return enGenerateGridErrorTypes::AREA_TYPE_NOT_SET;
    // }
    return { false, enGenerateGridErrorTypes::NO_ERROR };
}

nsEnvironment::EnvironmentErrorInformation nsEnvironment::Environment::draw_grid() {
    if(m_grid->size() == 0) {
        return { { true, enEnvironmentErrorTypes::grid_size_is_zero }, "The grid size is of size zero." };
    }
    else if (this->check_environment_settings().first) {
        return { { true, enEnvironmentErrorTypes::environment_settings_not_set }, "The settings of the environment is not yet set" };
    }
    std::cout << "Current search grid\n";
    for(unsigned x = 0; x < m_grid->size(); ++x) {
        for(unsigned y = 0; y < m_grid->at(x).size(); ++y)
            std::cout << m_grid->at(x).at(y);
    }
    return { };
}

nsEnvironment::GridTile nsEnvironment::Environment::generate_random_grid_tile(const nsCoord::Coord& current_coordinates) {
    AdjacentTiles f_temp_adjacent_tiles;
    nsEnvironment::GridTile f_return_tile = f_temp_adjacent_tiles.generate_random_grid_tile(this->m_grid, current_coordinates);
    return f_return_tile;
}

nsEnvironment::GenerateGridErrorInformation nsEnvironment::Environment::generate_grid() {
    if(this->check_environment_settings().first) {
        this->m_grid = std::shared_ptr<std::map<unsigned, std::vector<std::shared_ptr<nsTile::Tile>>>>(new std::map<unsigned, std::vector<std::shared_ptr<nsTile::Tile>>>);
        for(unsigned x = 0; x < this->m_settings.m_max_x; ++x) {
            for(unsigned y = 0;y < this->m_settings.m_max_y; ++y) {
                GridTile f_temp_tile = this->generate_random_grid_tile({x, y});
                if(f_temp_tile->get_tile_type() == nsTile::enTileType::target) {

                }
                (*this->m_grid)[x].push_back(f_temp_tile);
            }
        }
        return { };
    }
    return { this->check_environment_settings(), "GENERATE GRID ERROR"};
}

void nsEnvironment::Environment::reset_grid() {
    this->m_grid.reset();
    this->m_grid = nullptr;
}

nsEnvironment::EnvironmentTurnResult nsEnvironment::Environment::check_adjacent_tiles(const nsCoord::Coord& current_agent_location) {

}