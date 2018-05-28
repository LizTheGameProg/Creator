#pragma once

namespace LML
{
	class vec2;
	class vec3;

	class vec4
	{
	public:
		//--------------------------------
		// Constructors/Destructor
		//--------------------------------
		vec4();
		vec4(float all);
		vec4(vec3 vec, float w);
		vec4(vec2 vec, float z, float w);
		vec4(float x, float y, float z, float w);
		~vec4();

		//--------------------------------
		// Utility
		//--------------------------------
		float dot(vec4 other);
		vec4  cross(vec4 other);
		float magnitude();
		float magnitudeSquared();
		vec4  normalised();
		void  normalise();

		//--------------------------------
		// operators
		//--------------------------------
		vec4	operator+(vec4 other);
		vec4	operator-(vec4 other);
		vec4	operator*(float other);
		vec4	operator/(float other);
		vec4	operator=(vec4 other);
		bool	operator==(vec4 other);
		bool	operator!=(vec4 other);
		float & operator[](int index);

		//--------------------------------
		//variables
		//--------------------------------
		union
		{
			struct
			{
				float x;
				float y;
				float z;
				float w;
			};
			struct
			{
				float r;
				float g;
				float b;
				float a;
			};
			struct
			{
				float s;
				float t;
				float p;
				float q;
			};
			struct
			{
				float data[4];
			};
		};

		//--------------------------------
		// const static 'variables'
		//--------------------------------
		static const vec4 Up;
		static const vec4 Right;
		static const vec4 Forward;
	};

	//--------------------------------
	// non-member operators
	//--------------------------------
	vec4  operator*(float me, vec4 other);
	vec4  operator/(float me, vec4 other);

	//--------------------------------
	// non-member functions
	//--------------------------------
	float dot(vec4 me, vec4 other);
	float magnitude(vec4 me);
	float magnitudeSquared(vec4 me);
	vec4  normalised(vec4 me);
	void  normalise(vec4 me);
}