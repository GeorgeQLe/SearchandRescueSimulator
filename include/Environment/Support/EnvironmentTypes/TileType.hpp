/*  Copyright 2018 George Le

*/
#ifndef TILETYPE_HPP
#define TILETYPE_HPP

#include <map>
#include <utility>

namespace nsTileType {
    enum class TileType {
        NOTRELEVANT = -1,
        HOME, // the starting point(s) for searches
        PLAINS, // clear open space
        TREE, // shaded area from the sky
        SWAMP,
        HILL,
        MOUNTAIN,
        LAKE,
        RIVER,
        COUNT
    };

    struct TileProbability {
        TileProbability() { }

        TileType resolve_probabilities(unsigned int random_number) {
            std::map<TileType, std::pair<double, double>> f_probability_range;
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
            return TileType::NOTRELEVANT;
        }

        std::map<TileType, double> m_probabilities;
    };
}

#endif 