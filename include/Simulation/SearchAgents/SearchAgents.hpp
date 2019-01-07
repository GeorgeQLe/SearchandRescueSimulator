/*  Copyright 2018 George Le

    This file contains the declaration of the SearchAgent class 
    and its supporting enDirection enumerated class.
*/
#ifndef SEARCHAGENT_HPP
#define SEARCHAGENT_HPP

#include "Environment/Environment.hpp"

namespace nsSearchAgent {
    enum class enDirection {
        stay,
        up_left,
        up,
        up_right,
        right,
        down_right,
        down,
        down_left,
        left,
        count
    };

    enum class SearchAgentActionError {
        no_error,
        invalid_move,
        count
    };
    using SearchAgentActionErrorInformation = std::pair<bool, SearchAgentActionError>;

    struct SearchAgentActionResults {
        SearchAgentActionResults() { }
        SearchAgentActionResults(const SearchAgentActionErrorInformation& information, const std::string& error_message) : m_error(information), m_error_message(error_message) { }

        SearchAgentActionErrorInformation m_error = { false, SearchAgentActionError::no_error };
        std::string m_error_message = "Search Agent Action Results: NO ERROR YET";
    };

    class SearchAgentAction {
        public:
        virtual nsSearchAgent::SearchAgentActionErrorInformation execute() = 0;
    };

    class SearchAgent {
        public:
        SearchAgent() { }

        virtual nsCoord::Coord get_current_location() const = 0;
        
        private:
        nsEnvironment::AdjacentTiles current_adjacent_tiles;
    };
}

#endif // SEARCHAGENTS_HPP