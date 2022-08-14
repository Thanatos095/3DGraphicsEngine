#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>
#include <gl/glew.h>
#include <stb_image.h>
class Texture{
    public:
        Texture();
        Texture(const std::string& path);
        void load(const std::string& path);
        void bind();
        void unbind();
        ~Texture();
    private:
        unsigned int m_id;
};

#endif