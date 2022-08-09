#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include "Vertex.hpp"
#include "AttributeBuffer.hpp"
class Window;
class VertexArray{
    public:
        VertexArray(float * vertices, size_t sizeVertices, float *colors, size_t sizeColors, unsigned int *indices, size_t sizeIndices);
        static VertexArray LoadFromFile(const std::string &path);
        VertexArray();
        ~VertexArray();
        size_t getNumFaces() const;
        size_t getNumVertices() const;
        Vertex operator[](size_t i);
        void pushVertex(const Vertex& vertex);
        void pushFace(size_t v1, size_t v2, size_t v3);
    private:
        void bind();
        void unbind();
        void genBuffers();
        FloatBuffer m_vertices, m_colors;
        UintBuffer indices;
        bool initialized;
        unsigned int m_id;
        friend class Window;
};
#endif