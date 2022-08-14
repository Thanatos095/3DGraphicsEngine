#include "../headers/VertexArray.hpp"
#include "Utils.cpp"
VertexArray::VertexArray() : initialized(false){
}
// VertexArray::VertexArray(float * vertices, size_t sizeVertices, float *colors, size_t sizeColors, unsigned int *indices, size_t sizeIndices) {
//     this->m_positions.assign(vertices, vertices + sizeVertices);
//     // this->m_colors.assign(colors, colors + sizeColors);
//     this->indices.assign(indices, indices + sizeIndices);

//     this->genBuffers();
// }
VertexArray VertexArray::LoadFromFile(const std::string &path){
    VertexArray vao;
    std::string s;
    std::vector<std::string> faces;
    std::unordered_map<std::string, unsigned int> unique;
    float x, y, z;
    std::vector<float> p, u;
    std::ifstream fin(path);

    if(!fin)
        throw std::runtime_error("Error in opening the file");

    while(std::getline(fin, s))
    {
        std::istringstream words(s);
        std::string word;
        words >> word;
        if( word == "v"){
            words >> x >> y >> z;
            p.push_back(x); p.push_back(y); p.push_back(z);
        }
        else if(word == "vt"){
            words >> x >> y;
            u.push_back(x); u.push_back(y);
        }
        else if(word == "f"){
            words >> word;
            faces.push_back(word);
            words >> word;
            faces.push_back(word);
            words >> word;
            faces.push_back(word);
        }
    } 
    for(size_t i = 0, j=0 ; i < faces.size() ; i++){
        auto tokens = split(faces[i], "/");

        size_t posInd = std::stoi(tokens[0]) - 1;
        size_t texInd = std::stoi(tokens[1]) - 1;
        
        // std::cout << posInd << " " << texId << '\n';
        auto it = unique.find(faces[i]);
        if(it != unique.end()){
            vao.indices.push_back(it->second);
        }
        else{
            unique.insert(std::pair<std::string, unsigned int>(faces[i], j));
            
            vao.m_positions.push_back(p[posInd * 3]); 
            vao.m_positions.push_back(p[(posInd * 3) + 1]);
            vao.m_positions.push_back(p[(posInd * 3) + 2]);
            
            vao.m_texture_coordinates.push_back(u[texInd * 2]);
            vao.m_texture_coordinates.push_back(u[texInd*2 + 1]);

            vao.indices.push_back(j++);
        }
    }
    return vao;
}


VertexArray::~VertexArray(){
    glDeleteVertexArrays(1, &this->m_id);
}
size_t VertexArray::getNumFaces() const{
    return this->indices.size() / 3;
}
size_t VertexArray::getNumVertices() const{
    return this->m_positions.size() / 3;
}
void VertexArray::genBuffers(){
    glGenVertexArrays(1, &this->m_id);
    glBindVertexArray(this->m_id);

    this->m_positions.genBuffer(GL_ARRAY_BUFFER);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(GL_FLOAT), 0);

    this->m_texture_coordinates.genBuffer(GL_ARRAY_BUFFER);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 2 * sizeof(GL_FLOAT), 0);

    // this->m_colors.genBuffer(GL_ARRAY_BUFFER);
    // glEnableVertexAttribArray(2);
    // glVertexAttribPointer(2, 4, GL_FLOAT, false, 4 * sizeof(GL_FLOAT), 0);
    
    this->indices.genBuffer(GL_ELEMENT_ARRAY_BUFFER);
}
void VertexArray::bind(){
    if(initialized) glBindVertexArray(this->m_id);
    else{
        this->genBuffers();
        initialized = true;
    }
}
void VertexArray::unbind(){
    glBindVertexArray(0);
}