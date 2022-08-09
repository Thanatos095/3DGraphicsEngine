#ifndef UTILS_CPP
#define UTILS_CPP
#include <glm/glm.hpp>
#include <iostream>

inline void printVec(const glm::vec3 vec){
	std::cout << vec[0] << ' ' << vec[1] << ' ' << vec[2] << '\n'; 
}

#endif