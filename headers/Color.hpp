#ifndef COLOR_HPP
#define COLOR_HPP

class Color{
    public:
        float r, g, b, a;
        Color(float r, float g, float b, float a);
        Color(float r, float g, float b);
        Color(const Color &color);
        Color();
};

#endif