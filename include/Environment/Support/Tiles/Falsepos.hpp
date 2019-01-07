/*  Copyright 2018 George Le

*/
#ifndef FALSEPOS_HPP
#define FALSEPOS_HPP

#include "Environment/Support/EnvironmentTypes/TerrainType.hpp" // TileType
#include "Environment/Support/Tiles/Tile.hpp"

namespace nsFalsePositive {
    class FalsePositive : public nsTile::Tile {
        public:
        // 
        FalsePositive(const nsTerrainType::TerrainType new_tile_type, unsigned x, unsigned y) : nsTile::Tile(x, y, new_tile_type) {
            // set_symbol is a member function of the parent Tile
            // that changes the symbol that is printed during the
            // simulation
            this->set_symbol('-');
            this->set_tile_type(new_tile_type);
        }
        FalsePositive(const nsCoord::Coord& coordinates, const nsTerrainType::TerrainType new_tile_type) : nsTile::Tile(coordinates, new_tile_type) {
            // set_symbol is a member function of the parent Tile
            // that changes the symbol that is printed during the
            // simulation
            this->set_symbol('-');
            this->set_tile_type(new_tile_type);
        }

        /*-----------------------------------------------------------------------
            Called when this tile is searched and returns false most of the 
            time and true occassionally. This tile is meant to simulate potential
            inaccuracies that occur during a search.
        -----------------------------------------------------------------------*/
        virtual bool search() { return true; }
    };
}

#endif