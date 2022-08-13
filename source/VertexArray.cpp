#include "../headers/VertexArray.hpp"
VertexArray::VertexArray() : initialized(false){
}
VertexArray::VertexArray(float * vertices, size_t sizeVertices, float *colors, size_t sizeColors, unsigned int *indices, size_t sizeIndices) {
    this->m_vertices.assign(vertices, vertices + sizeVertices);
    this->m_colors.assign(colors, colors + sizeColors);
    this->indices.assign(indices, indices + sizeIndices);

    this->genBuffers();
}
VertexArray VertexArray::LoadFromFile(const std::string &path){
    VertexArray vao;
    std::string s;
    Vertex v;
    std::ifstream fin(path);
    if(!fin)
        throw std::runtime_error("Error in opening the file");

    while(std::getline(fin, s))
    {
        std::istringstream words(s);
        std::string word;
        words >> word;
        if( word == "v"){
            words >> v.x >> v.y >> v.z;
            vao.pushVertex(v);
        }
        else if(word == "f"){
            words >> v.x >> v.y >> v.z;
            vao.pushFace(v.x - 1, v.y - 1, v.z - 1);
        }
    } 
    vao.genBuffers(); 
    return vao;
}

VertexArray::~VertexArray(){
    glDeleteVertexArrays(1, &this->m_id);
}
size_t VertexArray::getNumFaces() const{
    return this->indices.size() / 3;
}
size_t VertexArray::getNumVertices() const{
    return this->m_vertices.size() / 3;
}
Vertex VertexArray::operator[](size_t i){
    size_t offset = i * 3;
    return Vertex(this->m_vertices[offset], 
                  this->m_vertices[offset + 1], 
                  this->m_vertices[offset + 2], 
                  Color(this->m_colors[offset], 
                        this->m_colors[offset + 1], 
                        this->m_colors[offset + 2]));
}

void VertexArray::pushVertex(const Vertex& vertex){
    if(initialized) return;
    this->m_vertices.push_back(vertex.x);
    this->m_vertices.push_back(vertex.y);
    this->m_vertices.push_back(vertex.z);
    this->m_colors.push_back(vertex.color.r);
    this->m_colors.push_back(vertex.color.g);
    this->m_colors.push_back(vertex.color.b);
    this->m_colors.push_back(vertex.color.a);
}
void VertexArray::pushFace(size_t v1, size_t v2, size_t v3){
    if(initialized) return;
    this->indices.push_back(v1);
    this->indices.push_back(v2);
    this->indices.push_back(v3);
}

void VertexArray::genBuffers(){
    glGenVertexArrays(1, &this->m_id);
    glBindVertexArray(this->m_id);

    this->m_vertices.genBuffer(GL_ARRAY_BUFFER);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(GL_FLOAT), 0);

    this->m_colors.genBuffer(GL_ARRAY_BUFFER);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, false, 4 * sizeof(GL_FLOAT), 0);
    
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