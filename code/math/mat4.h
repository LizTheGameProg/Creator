#pragma once

#include "vec4.h"

namespace LML
{
	class mat4
	{
	public:
		//--------------------------------
		// Constructors/Destructor
		//--------------------------------
		mat4();
		~mat4();

		//--------------------------------
		// Utility
		//--------------------------------
		mat4  transposed();
		mat4  inverse();
		float determinant();
		void  printToConsole();

		//--------------------------------
		// operators
		//--------------------------------
		mat4	operator*(float scalar);
		vec4	operator*(vec4 other);
		mat4	operator*(mat4 other);
		mat4	operator=(mat4 other);
		bool	operator==(mat4 other);
		bool	operator!=(mat4 other);
		vec4 &  operator[](int index);

		union
		{
			struct
			{
				vec4 m[4];
			};
			struct
			{
				float data[16];
			};
		};
	};

	mat4 operator*(float scalar, mat4 matrix);
}

#ifdef LML_TYPEDEFS
typedef LML::mat4 Matrix4;
#endif