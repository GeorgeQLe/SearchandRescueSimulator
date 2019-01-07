/*  Copyright 2018 George Le

*/
#ifndef COORD_HPP
#define COORD_HPP

namespace nsCoord {
    struct Coord {
        Coord(unsigned x, unsigned y) : m_x(x), m_y(y) { }
        Coord(const Coord& coord) : m_x(coord.m_x), m_y(coord.m_y) { }
        
        unsigned m_x = 0;
        unsigned m_y = 0;
    };
}

#endif