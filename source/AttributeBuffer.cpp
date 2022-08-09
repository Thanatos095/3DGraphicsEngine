#include "../headers/AttributeBuffer.hpp"
template<typename _Ty>
AttributeBuffer<_Ty>::AttributeBuffer(){
}

template<typename _Ty>
void AttributeBuffer<_Ty>::push_back(_Ty val){
	this->m_data.push_back(val);
}

template<typename _Ty>
void AttributeBuffer<_Ty>::assign(const _Ty* begin, const _Ty* end){
	this->m_data.assign(begin, end);
}
template<typename _Ty>
_Ty& AttributeBuffer<_Ty>::operator[](size_t i){
	return this->m_data[i];
}

template<typename _Ty>
size_t AttributeBuffer<_Ty>::size() const{
	return this->m_data.size();
}

template<typename _Ty>
void AttributeBuffer<_Ty>::bind() const{
	glBindBuffer(GL_ARRAY_BUFFER, this->m_id);
}

template<typename _Ty>
void AttributeBuffer<_Ty>::unbind() const{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template<typename _Ty>
void AttributeBuffer<_Ty>::genBuffer(GLenum	target){
	glGenBuffers(1, &this->m_id);
	glBindBuffer(target, this->m_id);
	glBufferData(target, sizeof(_Ty) * this->m_data.size(), this->m_data.data(), GL_STATIC_DRAW);
}

template<typename _Ty>
const unsigned int AttributeBuffer<_Ty>::getId() const{
    return this->m_id;
}

template<typename _Ty>
AttributeBuffer<_Ty>::~AttributeBuffer(){
    glDeleteBuffers(1, &this->m_id);
}

template class AttributeBuffer<float>;
template class AttributeBuffer<unsigned int>;