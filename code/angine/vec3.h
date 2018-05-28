#pragma once

namespace LML
{
	class vec3
	{
	public:
		//--------------------------------
		// Constructors/Destructor
		//--------------------------------
		vec3();
		vec3(float x, float y, float z);
		vec3(vec3 & other);
		~vec3();

		//--------------------------------
		// Operators
		//--------------------------------
		vec3 operator+(vec3 & other);
		vec3 operator-(vec3 & other);
		vec3 operator*(float other);
		vec3 operator/(float other);
		vec3 operator=(vec3 & other);
		vec3 operator+=(vec3 & other);
		vec3 operator-=(vec3 & other);
		vec3 operator*=(float other);
		vec3 operator/=(float other);
		bool operator==(vec3 & other);
		float& operator[](int index);

		//--------------------------------
		// Utilities
		//--------------------------------
		float magnitude();
		float length();
		vec3 normalised();
		float dot(vec3 & other);
		vec3 cross(vec3 & other);

		//--------------------------------
		// Variables
		//--------------------------------
		union
		{
			struct { float x, y, z; };
			struct { float r, g, b; };
			struct { float s, t, p; };
		};

		const static vec3 Up;
		const static vec3 Right;
		const static vec3 Forward;
	};
}