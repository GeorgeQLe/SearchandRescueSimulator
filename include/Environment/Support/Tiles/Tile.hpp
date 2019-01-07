/*  Copyright 2018 George Le

    This file contains the declaration of the Tile class and its supporting structs and enumerated classes.
*/
#ifndef TILE_HPP
#define TILE_HPP

#include <iostream> // std::ostream

#include "Environment/Support/Coord.hpp" // Coord
#include "Environment/Support/EnvironmentTypes/TerrainType.hpp" // TerrainType

namespace nsTile {
    enum class enSearchErrorType {
        no_error,
        using_base_class,
        count
    };
    using SearchError = std::pair<bool, enSearchErrorType>;

    struct SearchErrorInformation {
        SearchErrorInformation() { }
        SearchErrorInformation(const SearchError& error, const std::string& error_message) {
            if(error.first) {
                m_error = error;
                m_error_message = error_message;
            }
        }
        
        SearchError m_error = { false, enSearchErrorType::no_error };
        std::string m_error_message = "NO ERROR YET";
    };

    enum class enTileType {
        notrelevant,
        empty,
        falsepos,
        target,
        count
    };

    class Tile {
        public:
        // required for the class constructor is the x and y coordinates for 
        // the tile
        Tile(unsigned x, unsigned y, const nsTerrainType::TerrainType& new_tile_type) : m_tile_coords(x, y), m_terrain_type(new_tile_type) { }
        Tile(const nsCoord::Coord& coordinates, const nsTerrainType::TerrainType& new_tile_type) : m_tile_coords(coordinates), m_terrain_type(new_tile_type) { }

        // accessor function
        nsTerrainType::TerrainType get_terrain_type() const { return m_terrain_type; } 
        enTileType get_tile_type() const { return m_tile_type; }

        // mutator function
        void set_tile_type(const nsTerrainType::TerrainType& new_tile_type) { m_terrain_type = new_tile_type; }

        /*-----------------------------------------------------------------
            This function simulates a search of this tile on the grid and
            returns whether the target of the search is in the tile or not.
            The function is a pure virtual function 
        -----------------------------------------------------------------*/
        virtual bool search() = 0;

        /*--------------------------------------------------------------------
            This function sets the symbol to be printed out when the tile is
            printed by the simulation.
        --------------------------------------------------------------------*/
        void set_symbol(char c) { m_symbol = c; }

        /*--------------------------------------------------------------------
            This function overloads the insertion operator to print out the
            symbol for the simulation.
        --------------------------------------------------------------------*/
        friend std::ostream& operator<<(std::ostream& output, const Tile* tile) {
            output << tile->m_symbol;
            return output;
        }

        private:
        // the default constructor of the class is private to force usage of the 
        // parameterized constructor (see above)
        Tile() : m_tile_coords(-1, -1) {}

        nsCoord::Coord m_tile_coords;
        nsTerrainType::TerrainType m_terrain_type;
        enTileType m_tile_type;

        // the symbol for a tile 
        char m_symbol;
    };
}

#endif