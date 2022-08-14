#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <AttributeBuffer.hpp>
class Window;
class VertexArray{
    public:
        // VertexArray(float * vertices, size_t sizeVertices, float *colors, size_t sizeColors, unsigned int *indices, size_t sizeIndices);
        static VertexArray LoadFromFile(const std::string &path);
        VertexArray();
        ~VertexArray();
        size_t getNumFaces() const;
        size_t getNumVertices() const;
    private:
        void bind();
        void unbind();
        void genBuffers();
        FloatBuffer m_positions, m_texture_coordinates;
        UintBuffer indices;
        bool initialized;
        unsigned int m_id;
        friend class Window;
};
#endif