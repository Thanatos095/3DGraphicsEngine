#ifndef ATTRIBUTEBUFFER_HPP
#define ATTRIBUTEBUFFER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

template<typename _Ty>
class AttributeBuffer{
    public:
        AttributeBuffer();
        ~AttributeBuffer();
        void push_back(_Ty val);
        void assign(const _Ty* begin, const _Ty* end);
        _Ty& operator[](size_t i);
        size_t size() const;
        void bind() const;
        void unbind() const;
        void genBuffer(GLenum target);
        const unsigned int getId() const;
    private:
        std::vector<_Ty> m_data;
        unsigned int m_id;
};
using FloatBuffer = AttributeBuffer<float>;
using UintBuffer = AttributeBuffer<unsigned int>;

#endif