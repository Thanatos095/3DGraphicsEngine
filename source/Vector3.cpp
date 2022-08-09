#include "../headers/Vector3.hpp"
template<typename _Ty>
Vector3<_Ty>::Vector3(std::initializer_list<_Ty> init) : x((*this)[0]), y((*this)[1]), z((*this)[2]){
	assert(init.size() == 3);
	this->x = *(init.begin());
	this->y = *(init.begin() + 1);
	this->z = *(init.begin() + 2);
}

template<typename _Ty>
Vector3<_Ty>::Vector3(const glm::vec<3, _Ty, glm::defaultp> &vec) : x((*this)[0]), y((*this)[1]), z((*this)[2]){
	this->x = vec[0];
	this->y = vec[1];
	this->z = vec[2];
}

template<typename _Ty>
Vector3<_Ty>::Vector3() : x((*this)[0]), y((*this)[1]), z((*this)[2]){
	this->x = this->y = z = 0;
}

template<typename _Ty>
Vector3<_Ty>& Vector3<_Ty>::operator=(const glm::vec<3, _Ty, glm::defaultp> &vec){
	this->x = vec[0];
	this->y = vec[1];
	this->z = vec[2];
	return *this;
}

template<typename _Ty>
std::ostream& operator<<(std::ostream &ostr, Vector3<_Ty> &vec){
   ostr << '('<< vec.x << ", "<< vec.y << ", " << vec.z << ')';
   return ostr;
}
