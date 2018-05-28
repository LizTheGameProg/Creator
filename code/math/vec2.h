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
		vec2(float both);
		vec2(float x, float y);
		~vec2();

		//--------------------------------
		// Utility
		//--------------------------------
		float dot(vec2 other);
		float magnitude();
		float magnitudeSquared();
		vec2  normalised();
		void  normalise();
		float angle();

		//--------------------------------
		// member operators
		//--------------------------------
		vec2	operator+(vec2 other);
		vec2	operator-(vec2 other);
		vec2	operator*(float other);
		vec2	operator/(float other);
		vec2	operator=(vec2 other);
		bool	operator==(vec2 other);
		bool	operator!=(vec2 other);
		float & operator[](int index);
		vec2	operator+=(vec2 other);
		vec2	operator-=(vec2 other);
		vec2	operator*=(float other);
		vec2	operator/=(float other);

		//--------------------------------
		//variables
		//--------------------------------
		union
		{
			struct
			{
				float x;
				float y;
			};
			struct
			{
				float u;
				float v;
			};
			struct
			{
				float data[2];
			};
		};

		//--------------------------------
		// const static 'variables'
		//--------------------------------
		static const vec2 Up;
		static const vec2 Right;

	};

	//--------------------------------
	// non-member operators
	//--------------------------------
	vec2  operator*(float me, vec2 other);
	vec2  operator/(float me, vec2 other);

	//--------------------------------
	// non-member functions
	//--------------------------------
	float dot(vec2 me, vec2 other);
	float magnitude(vec2 me);
	float magnitudeSquared(vec2 me);
	vec2  normalised(vec2 me);
	void  normalise(vec2 me);
}

#ifdef LML_TYPEDEFS
typedef LML::vec2 Vector2;
#endif