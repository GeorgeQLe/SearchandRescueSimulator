#ifndef SEARCHAGENT_HPP
#define SEARCHAGENT_HPP

#include "Environment/Support/Tiles/Tile.hpp"

namespace nsSearchAgent {
    enum class enDirection {
        STAY,
        UP_LEFT,
        UP,
        UP_RIGHT,
        RIGHT,
        DOWN_RIGHT,
        DOWN,
        DOWN_LEFT,
        LEFT,
        COUNT
    };

    class SearchAgent {
        public:
        SearchAgent() { }

        virtual enDirection move() = 0;
        virtual enDirection search() = 0;
    };
}

#endif