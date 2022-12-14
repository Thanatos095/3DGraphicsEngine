#include <Texture.hpp>
Texture::Texture(){
    std::cout << "Textureeee :>\n";
}

Texture::Texture(const std::string& path){
    this->load(path);
}
void Texture::load(const std::string& path){
    glGenTextures(1, &this->m_id);
    glBindTexture(GL_TEXTURE_2D, this->m_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    

    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if(data == NULL) throw std::runtime_error(stbi_failure_reason() + std::string(". Could not load texture."));
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}
void Texture::bind(){
    glBindTexture(GL_TEXTURE_2D, this->m_id);
}
void Texture::unbind(){
    glBindTexture(GL_TEXTURE_2D, 0);
}
Texture::~Texture(){
    glDeleteTextures(1, &this->m_id);
}