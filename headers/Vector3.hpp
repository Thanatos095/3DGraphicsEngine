#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include <iostream>
#include <glm/glm.hpp>

template <typename _Ty>
class Vector3 : public glm::vec<3, _Ty, glm::defaultp>{
	public:
		_Ty &x, &y, &z;
		Vector3(std::initializer_list<_Ty> init);
		Vector3(const glm::vec<3, _Ty, glm::defaultp> &vec);
		Vector3();
		Vector3& operator=(const glm::vec<3, _Ty, glm::defaultp> &vec);
	private:
		Vector3& operator=(const Vector3<_Ty> &vec) = delete;
};
template <typename _T>
std::ostream& operator<<(std::ostream &ostr, Vector3<_T> &vec);

using Vector3f = Vector3<float>;
using Vector3i = Vector3<int>;
using Vector3u = Vector3<unsigned int>;


#endif