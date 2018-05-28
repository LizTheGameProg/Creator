#pragma once

#include "vec2.h"

namespace LML
{
	class mat2
	{
	public:
		//--------------------------------
		// Constructors/Destructor
		//--------------------------------
		mat2();
		mat2(float m00, float m01, float m10, float m11);
		~mat2();

		//--------------------------------
		// Utility
		//--------------------------------
		mat2  transposed();
		mat2  inverse();
		float determinant();
		void  printToConsole();

		//--------------------------------
		// operators
		//--------------------------------
		mat2	operator*(float scalar);
		vec2	operator*(vec2 other);
		mat2	operator*(mat2 other);
		vec2 &  operator[](int index);
		mat2	operator=(mat2 other);
		bool	operator==(mat2 other);
		bool	operator!=(mat2 other);

		union
		{
			struct
			{
				vec2 m[2];
			};
			struct
			{
				float data[4];
			};
		};
	};
	mat2 operator*(float scalar, mat2 matrix);
}

#ifdef LML_TYPEDEFS
typedef LML::mat2 Matrix2;
#endif