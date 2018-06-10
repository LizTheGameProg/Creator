#pragma once
#include "vec3.h"

namespace ANGINE
{
	class mat3
	{
	public:
		//--------------------------------
		// Constructors/Destructor
		//--------------------------------
		mat3();
		mat3(vec3 & v0, vec3 & v1, vec3 & v2);
		mat3(mat3 & other);
		~mat3();

		//--------------------------------
		// Operators
		//--------------------------------
		mat3 operator+(mat3 & other);
		mat3 operator-(mat3 & other);
		vec3 operator*(vec3 & other);
		mat3 operator*(mat3 & other);
		vec3 & operator[](int index);
		//--------------------------------
		// Utilities
		//--------------------------------
		// TODO: transpose, inverse

		//--------------------------------
		// Variables
		//--------------------------------
		vec3 data[3];
	};
}