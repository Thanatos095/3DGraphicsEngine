#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "Color.hpp"

class Vertex{
    public:
        Vertex(float x, float y, float z, Color color);
        Vertex();
        float x, y, z;
        Color color;

};

#endif
