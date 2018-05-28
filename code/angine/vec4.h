#pragma once

namespace LML
{
	class vec4
	{
	public:
		//--------------------------------
		// Constructors/Destructor
		//--------------------------------
		vec4();
		vec4(float x, float y, float z, float w = 0);
		vec4(vec4 & other);
		~vec4();

		//--------------------------------
		// Operators
		//--------------------------------
		vec4 operator+(vec4 & other);
		vec4 operator-(vec4 & other);
		vec4 operator*(float other);
		vec4 operator/(float other);
		vec4 operator=(vec4 & other);
		vec4 operator+=(vec4 & other);
		vec4 operator-=(vec4 & other);
		vec4 operator*=(float other);
		vec4 operator/=(float other);
		bool operator==(vec4 & other);

		//--------------------------------
		// Utilities
		//--------------------------------
		// TODO: magnitude, normalised, dot, cross
		float magnitude();
		float length();
		vec4  normalised();
		float dot(vec4 & other);
		vec4  cross(vec4 & other);

		//--------------------------------
		// Variables
		//--------------------------------
		union
		{
			struct { float x, y, z, w; };
			struct { float r, g, b, a; };
			struct { float s, t, p, q; };
		};

		const static vec4 Up;
		const static vec4 Right;
		const static vec4 Forward;
	};
}