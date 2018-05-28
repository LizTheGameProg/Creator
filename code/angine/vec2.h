#pragma once

namespace LML
{
	class vec2
	{
	public:
		//--------------------------------
		// Constructors/Destructor
		//--------------------------------
		vec2();
		vec2(float x, float y);
		vec2(vec2 & other);
		~vec2();

		//--------------------------------
		// Operators
		//--------------------------------
		vec2 operator+(vec2 & other);
		vec2 operator-(vec2 & other);
		vec2 operator*(float other);
		vec2 operator/(float other);
		vec2 operator=(vec2 & other);
		vec2 operator+=(vec2 & other);
		vec2 operator-=(vec2 & other);
		vec2 operator*=(float other);
		vec2 operator/=(float other);
		bool operator==(vec2 & other);

		//--------------------------------
		// Utilities
		//--------------------------------
		// magnitude, normalize, dot
		float magnitude();
		float length();
		vec2 normalised();
		float dot(vec2 & other);

		//--------------------------------
		// Variables
		//--------------------------------
		union
		{
			struct { float x, y; };
			struct { float r, g; };
			struct { float s, t; };
			struct { float u, v; };
		};
		const static vec2 Up;
		const static vec2 Right;
	};
}