#include <TextureManager.hpp>

Texture& TextureManager::getTexture(const std::string& path){
    auto it = this->m_textures.find(path);
    if(it == this->m_textures.end()){
        this->m_textures.emplace(path, path);
        return this->m_textures.find(path)->second;
    }
    return it->second;
}
void TextureManager::deleteTexture(const std::string& path){
    auto it = this->m_textures.find(path);
    if(it == this->m_textures.end()) throw std::runtime_error("This texture was not found in the manager!");
    this->m_textures.erase(it);
}
size_t TextureManager::numberOfTextures(){
    return this->m_textures.size();
}