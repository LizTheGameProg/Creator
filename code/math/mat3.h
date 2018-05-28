#pragma once

#include "vec3.h"

namespace LML
{
	class mat3
	{
	public:
		//--------------------------------
		// Constructors/Destructor
		//--------------------------------
		mat3();
		mat3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22);
		~mat3();

		//--------------------------------
		// Utility
		//--------------------------------
		mat3  transposed();
		mat3  inverse();
		float determinant();
		void  printToConsole();

		//--------------------------------
		// operators
		//--------------------------------
		mat3	operator*(float scalar);
		vec3	operator*(vec3 other);
		mat3	operator*(mat3 other);
		mat3	operator=(mat3 other);
		bool	operator==(mat3 other);
		bool	operator!=(mat3 other);
		vec3 &  operator[](int index);

		union
		{
			struct
			{
				vec3 m[3];
			};
			struct
			{
				float data[9];
			};
		};
	};
	mat3 operator*(float scalar, mat3 matrix);
}

#ifdef LML_TYPEDEFS
typedef LML::mat3 Matrix3;
#endif