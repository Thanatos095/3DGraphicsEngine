#include "../headers/Color.hpp"

Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a){}
Color::Color(const Color &color) : r(color.r), g(color.g), b(color.b), a(color.a){}
Color::Color(float r, float g, float b) : r(r), g(g), b(b){}
Color::Color():r(1.f), g(1.f), b(1.f), a(1.f){}