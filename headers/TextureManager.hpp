#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP
#include <unordered_map>
#include <Texture.hpp>
#include <iostream>
class TextureManager{
    public:
        Texture& getTexture(const std::string& path);
        void deleteTexture(const std::string& path);
        size_t numberOfTextures();
    private:
        void loadTexture(const std::string& path);
        std::unordered_map<std::string, Texture> m_textures;
};

#endif