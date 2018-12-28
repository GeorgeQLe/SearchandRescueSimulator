/*  Copyright 2018 George Le

    Declares and defines the Empty class 
*/
#ifndef EMPTY_HPP
#define EMPTY_HPP

#include "Environment/Support/EnvironmentTypes/TileType.hpp" // TileType
#include "Environment/Support/Tiles/Tile.hpp"

namespace nsEmpty {
    class Empty : public nsTile::Tile {
        public:
        //
        Empty(const nsTileType::TileType new_tile_type, unsigned x, unsigned y) : nsTile::Tile(x, y, new_tile_type) {
            // set_symbol is a member function of the parent Tile
            // that changes the symbol that is printed during the
            // simulation
            this->set_symbol(' ');
        }
        Empty(const nsCoord::Coord& coordinates, const nsTileType::TileType new_tile_type) : nsTile::Tile(coordinates, new_tile_type) {
            // set_symbol is a member function of the parent Tile
            // that changes the symbol that is printed during the
            // simulation
            this->set_symbol(' ');
        }

        /*--------------------------------------------------------------------
            This function simulates a search of this tile on the grid and
            returns whether the target of the search is in the tile or not.
        --------------------------------------------------------------------*/
        virtual bool search() { return false; }
    };
}

#endif