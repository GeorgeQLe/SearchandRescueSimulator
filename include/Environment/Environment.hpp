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
    using GridTile = std::shared_ptr<nsTile::Tile>;
    using GridColumn = std::vector<GridTile>;
    using Grid = std::map<unsigned, GridColumn>;
    using EnvironmentGrid = std::shared_ptr<Grid>;

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
        nsTileType::TileType count_tile_probabilities();

        // mutator function
        void set_adjacent_tile_types(const nsEnvironment::EnvironmentGrid& sim_grid, const nsCoord::Coord& current_coords);
        
        nsEnvironment::GridTile m_tiles[8] = { nullptr };
    };

    enum class enEnvironmentErrorTypes {
        NO_ERROR,
        GRID_SIZE_IS_ZERO,
        ENVIRONMENT_SETTINGS_NOT_SET,
        COUNT
    };
    using EnvironmentError = std::pair<bool, enEnvironmentErrorTypes>;

    struct EnvironmentErrorInformation {
        EnvironmentErrorInformation() { }
        EnvironmentErrorInformation(const EnvironmentError& error, const std::string& error_message) : m_error(error), m_error_message(error_message) { }

        EnvironmentError m_error = { false, enEnvironmentErrorTypes::NO_ERROR };
        std::string m_error_message = "NO ERROR YET";
    };

    struct EnvironmentFinalResult {
        EnvironmentFinalResult() { }


    };

    struct EnvironmentTurnResult {
        EnvironmentTurnResult() { }


    };

    struct EnvironmentSetting {
        EnvironmentSetting() { }
        EnvironmentSetting(unsigned max_x, unsigned max_y, nsAreaType::AreaType area_type) : m_max_x(max_x), m_max_y(max_y), m_area_type(area_type) {}

        unsigned m_max_x = 0;
        unsigned m_max_y = 0;
        nsAreaType::AreaType m_area_type = nsAreaType::AreaType::VOID;
    };

    enum class enGenerateGridErrorTypes {
        NO_ERROR,
        AREA_TYPE_NOT_SET,
        MAX_X_VALUE_NOT_SET,
        MAX_Y_VALUE_NOT_SET,
        COUNT
    };
    using GenerateGridError = std::pair<bool, enGenerateGridErrorTypes>;

    struct GenerateGridErrorInformation {
        GenerateGridErrorInformation() { }
        GenerateGridErrorInformation(const GenerateGridError& error, std::string error_message) : m_error(error), m_error_message(error_message) { }

        GenerateGridError m_error = { false, enGenerateGridErrorTypes::NO_ERROR };
        std::string m_error_message = "NO ERROR YET";
    };

    class Environment {
        public:
        Environment() : m_grid(nullptr) { }

        void set_environment(unsigned max_x, unsigned max_y) { m_settings.m_max_x = max_x; m_settings.m_max_y = max_y; }
        void set_environment(unsigned max_x, unsigned max_y, nsAreaType::AreaType area_type) { m_settings.m_max_x = max_x; m_settings.m_max_y = max_y; m_settings.m_area_type = area_type; }
        
        /*-----------------------------------------------------------------
            This function generates a random grid based on the settings of
            the environment.
        -----------------------------------------------------------------*/
        GenerateGridErrorInformation generate_grid();

        /*-------------------------------------------------------------
            This function removes the grid that is held in this class.
        -------------------------------------------------------------*/
        void reset_grid();

        EnvironmentTurnResult resolve_turn();
        EnvironmentFinalResult resolve_final_turn();

        private:
        /*----------------------------------------------------------------
            This function checks that the Environment's settings has been 
            initialized before the grid is initialized.
        ----------------------------------------------------------------*/
        GenerateGridError check_environment_settings();

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