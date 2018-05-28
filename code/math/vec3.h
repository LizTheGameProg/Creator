#pragma once

namespace LML
{
	class vec2;

	class vec3
	{
	public:
		//--------------------------------
		// Constructors/Destructor
		//--------------------------------
		vec3();
		vec3(float all);
		vec3(vec2 vec, float z);
		vec3(float x, float y, float z);
		~vec3();

		//--------------------------------
		// Utility
		//--------------------------------
		float dot(vec3 other);
		vec3  cross(vec3 other);
		float magnitude();
		float magnitudeSquared();
		vec3  normalised();
		void  normalise();
		vec2  xy();

		//--------------------------------
		// operators
		//--------------------------------
		vec3	operator+(vec3 other);
		vec3	operator-(vec3 other);
		vec3	operator*(float other);
		vec3	operator/(float other);
		vec3	operator=(vec3 other);
		bool	operator==(vec3 other);
		bool	operator!=(vec3 other);
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
			};
			struct
			{
				float r;
				float g;
				float b;
			};
			struct
			{
				float data[3];
			};
		};

		//--------------------------------
		// const static 'variables'
		//--------------------------------
		static const vec3 Up;
		static const vec3 Right;
		static const vec3 Forward;
	};

	//--------------------------------
	// non-member operators
	//--------------------------------
	vec3  operator*(float me, vec3 other);
	vec3  operator/(float me, vec3 other);

	//--------------------------------
	// non-member functions
	//--------------------------------
	float dot(vec3 me, vec3 other);
	float magnitude(vec3 me);
	float magnitudeSquared(vec3 me);
	vec3  normalised(vec3 me);
	void  normalise(vec3 me);
}

#ifdef LML_TYPEDEFS
typedef LML::vec3 Vector3;
#endif