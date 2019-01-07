/*  Copyright 2018 George Le

    This file provides the declaration of the TerrainType enumerated class and the TileProbability struct
    that supports the main Tile class.
*/
#ifndef TERRAINTYPE_HPP
#define TERRAINTYPE_HPP

#include <map>
#include <utility>

namespace nsTerrainType {
    enum class TerrainType {
        notrelevant = -1,
        home, // the starting point(s) for searches
        plains, // clear open space
        forest, // shaded area from the sky
        swamp,
        hill,
        mountain,
        lake, // please take lakes and rivers as tribute bc islands would have been a nightmare
        river,
        count
    };
    using Adjacent_terrain_count = std::map<TerrainType, unsigned>;

    //void count

    struct TileProbability {
        TileProbability() { }

        TerrainType resolve_probabilities(unsigned int random_number) {
            std::map<TerrainType, std::pair<double, double>> f_probability_range;
            double f_current_probability_cap = 0.0;

            for(auto it = this->m_probabilities.begin(); it != this->m_probabilities.end(); ++it) {
                f_probability_range[it->first].first = f_current_probability_cap;
                f_current_probability_cap += it->second;
                f_probability_range[it->first].second = f_current_probability_cap;
            }

            for(auto it = f_probability_range.begin(); it != f_probability_range.end(); ++it) {
                if(random_number > it->second.first && random_number <= it->second.second) {
                    return it->first;
                }
            }
            return TerrainType::notrelevant;
        }

        std::map<TerrainType, double> m_probabilities;
    };
}

#endif 