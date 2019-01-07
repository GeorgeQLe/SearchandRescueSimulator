/*  Copyright 2018 George Le

    This file contains the definition for the SearchAgentTypes enumerated class
    that allows for the simulation to know what the available types of search
    agents are.
*/
#ifndef SEARCHAGENTTYPES_HPP
#define SEARCHAGENTTYPES_HPP

namespace nsSearchAgentTypes {
    enum class SearchAgentTypes {
        NO_AGENT_TYPE,
        AERIAL_DRONE,
        COUNT
    };
}

#endif