/*  Copyright 2018 George Le

*/
#ifndef TARGET_HPP
#define TARGET_HPP

#include "Environment/Support/EnvironmentTypes/TileType.hpp" // TileType
#include "Environment/Support/Tiles/Tile.hpp"

namespace nsTarget {
    class Target : public nsTile::Tile {
        public:
        Target(const nsTileType::TileType& new_tile_type, unsigned x, unsigned y) : nsTile::Tile(x, y, new_tile_type) {
            // set_symbol is a member function of the parent Tile
            // that changes the symbol that is printed during the
            // simulation
            this->set_symbol('+');
            this->set_tile_type(new_tile_type);
        }
        Target(const nsCoord::Coord& coordinates, const nsTileType::TileType& new_tile_type) : nsTile::Tile(coordinates, new_tile_type) {
            // set_symbol is a member function of the parent Tile
            // that changes the symbol that is printed during the
            // simulation
            this->set_symbol('+');
            this->set_tile_type(new_tile_type);
        }
        /*--------------------------------------------------------------------
            This function simulates a search of this tile on the grid and
            returns whether the target of the search is in the tile or not.
        --------------------------------------------------------------------*/
        virtual bool search() { return true; }
    };
}

#endif