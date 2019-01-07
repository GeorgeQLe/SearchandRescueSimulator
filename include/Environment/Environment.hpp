/*  Copyright 2018 George Le

    This file provides the declaration of the Environment class and its supporting structures
    and files.
*/
#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <map> // std::map
#include <memory> // std::shared_ptr
#include <vector> // std::vector

#include "Environment/Support/EnvironmentTypes/AreaType.hpp"
#include "Environment/Support/Tiles/Tile.hpp"

namespace nsEnvironment {
    // Various convenient using-declarations
    using GridTile = std::shared_ptr<nsTile::Tile>;
    using GridColumn = std::vector<GridTile>;
    using Grid = std::map<unsigned, GridColumn>;
    using EnvironmentGrid = std::shared_ptr<Grid>;

    /*
        This struct is used to determine and store the 
        adjacent tiles for a given coordinate.
    */
    struct AdjacentTiles {
        AdjacentTiles() { }

        /*--------------------------------------------------------------------------------
            This function assists the Environment class in generating a random grid tile.
        --------------------------------------------------------------------------------*/
        nsEnvironment::GridTile generate_random_grid_tile(const nsEnvironment::EnvironmentGrid& sim_grid, const nsCoord::Coord& current_coords);
        /*--------------------------------------------------------------------------------
            This function assists the generate_random_grid_tile function in calculating
            what the probabilities
        --------------------------------------------------------------------------------*/
        nsTerrainType::TerrainType count_tile_probabilities();

        // mutator function
        void set_adjacent_tile_types(const nsEnvironment::EnvironmentGrid& sim_grid, const nsCoord::Coord& current_coords);
        
        nsEnvironment::GridTile m_tiles[8] = { nullptr };
    };

    /*
        These enumerated values detail various errors
        that can occur during the running of a function
        in the Environment class.
    */
    enum class enEnvironmentErrorTypes {
        no_error,
        grid_size_is_zero,
        environment_settings_not_set,
        count
    };
    using EnvironmentError = std::pair<bool, enEnvironmentErrorTypes>;

    /*
        This struct is returned from any of the member functions 
        that performs an operation on or with the environment class.
        This struct is returned by the EnvironmentTurnResult struct
        as a potential error message.
    */
    struct EnvironmentErrorInformation {
        EnvironmentErrorInformation() { }
        EnvironmentErrorInformation(const EnvironmentError& error, const std::string& error_message) : m_error(error), m_error_message(error_message) { }

        EnvironmentError m_error = { false, enEnvironmentErrorTypes::no_error };
        std::string m_error_message = "NO ERROR YET";
    };

    /*
        This struct is returned by the Environment class's
        check_adjacent_tiles function and forms the basis of
        a search agent's ability to choose which direction
        it is going to move in and for it to search a tile
        for a target.
    */
    struct EnvironmentTurnResult {
        EnvironmentTurnResult() { }
        EnvironmentTurnResult(const AdjacentTiles& new_adjacent_tiles, bool found_all_targets, bool move_possible) : m_adjacent_tiles(new_adjacent_tiles), m_found_all_targets(found_all_targets), m_possible_move(move_possible) { }

        AdjacentTiles m_adjacent_tiles;
        bool m_found_all_targets = false;
        bool m_possible_move = false;

        EnvironmentErrorInformation m_error_information;
    };

    /*
        This struct tracks the various settings for the Environment
        class and should be set before the Environment class is used.
        Its default values will cause the Environment class to return
        an error.
    */
    struct EnvironmentSetting {
        EnvironmentSetting() { }
        EnvironmentSetting(unsigned max_x, unsigned max_y, nsAreaType::AreaType area_type) : m_max_x(max_x), m_max_y(max_y), m_area_type(area_type) {}

        unsigned m_max_x = 0;
        unsigned m_max_y = 0;
        nsAreaType::AreaType m_area_type = nsAreaType::AreaType::VOID;
    };

    /*
        These enumerated values detail the various errors that the 
        Environment class can encounter while attempting to generate 
        itself.
    */
    enum class enGenerateGridErrorTypes {
        NO_ERROR,
        AREA_TYPE_NOT_SET,
        MAX_X_VALUE_NOT_SET,
        MAX_Y_VALUE_NOT_SET,
        COUNT
    };
    using GenerateGridError = std::pair<bool, enGenerateGridErrorTypes>;

    /*
        This struct is the error returned after an attempted generation of
        a grid class. It contains a pair of a boolean value which tracks
        whether or not there was an error and one of the above enumerated 
        class values which details what caused there to an error as well
        as a string which contains a specific debug/log message for what
        happened.
    */
    struct GenerateGridErrorInformation {
        GenerateGridErrorInformation() { }
        GenerateGridErrorInformation(const GenerateGridError& error, std::string error_message) : m_error(error), m_error_message(error_message) { }

        GenerateGridError m_error = { false, enGenerateGridErrorTypes::NO_ERROR };
        std::string m_error_message = "NO ERROR YET";
    };

    class Environment {
        public:
        // default constructor
        Environment() : m_grid(nullptr) { }

        // mutator functions
        void set_environment(unsigned max_x, unsigned max_y) { m_settings.m_max_x = max_x; m_settings.m_max_y = max_y; }
        void set_environment(unsigned max_x, unsigned max_y, nsAreaType::AreaType area_type) { m_settings.m_max_x = max_x; m_settings.m_max_y = max_y; m_settings.m_area_type = area_type; }
        
        /*--------------------------------------------------------------------
            This function is the primary workhorse for the Environment class
            as it is used to get the surrounding area of the search agent
            as well as if they are making an invalid move (by moving outside
            the valid search area of the grid) or if they found one or all of
            the targets.
        ---------------------------------------------------------------------*/
        EnvironmentTurnResult check_adjacent_tiles(const nsCoord::Coord& current_agent_location);

        /*----------------------------------------------------------------
            This function checks that the Environment's settings has been 
            initialized before the grid is initialized.
        ----------------------------------------------------------------*/
        GenerateGridError check_environment_settings();

        /*-----------------------------------------------------------------
            This function generates a random grid based on the settings of
            the environment.
        -----------------------------------------------------------------*/
        GenerateGridErrorInformation generate_grid();

        /*-------------------------------------------------------------
            This function removes the grid that is held in this class.
        -------------------------------------------------------------*/
        void reset_grid();

        private:
        /*--------------------------------------------------------------------
            This function draws the grid that is contained in the environment.
        --------------------------------------------------------------------*/
        EnvironmentErrorInformation draw_grid();

        /*------------------------------------------------------------------
            This function generates random grid tiles based on the adjacent
            tiles and the simulation area type.
        ------------------------------------------------------------------*/
        GridTile generate_random_grid_tile(const nsCoord::Coord& current_coordinates);

        EnvironmentGrid m_grid;
        EnvironmentSetting m_settings;
    };
}

#endif