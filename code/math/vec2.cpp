#include "vec2.h"
#include "common (2).h"

namespace LML
{
	const vec2 vec2::Up = vec2(0.f, 1.f);
	const vec2 vec2::Right = vec2(1.f, 0.f);

	//--------------------------------
	// Constructors/Destructor
	//--------------------------------
	vec2::vec2()
	{
		x = 0.f;
		y = 0.f;
	}

	vec2::vec2(float a_both)
	{
		x = a_both;
		y = a_both;
	}

	vec2::vec2(float a_x, float a_y)
	{
		x = a_x;
		y = a_y;
	}
	
	vec2::~vec2()
	{

	}

	//--------------------------------
	// Utility
	//--------------------------------
	float vec2::dot(vec2 other)
	{
		return x * other.x + y * other.y;
	}

	float vec2::magnitude()
	{
		return sqrt(x * x + y * y);
	}

	float vec2::magnitudeSquared()
	{
		return x * x + y * y;
	}

	vec2 vec2::normalised()
	{
		vec2 norm;
		if(magnitudeSquared() != 0.f)
		{
			float mag = magnitude();
			norm.x = x / mag;
			norm.y = y / mag;
		}
		return norm;
	}

	void vec2::normalise()
	{
		if(magnitudeSquared() != 0.f)
		{
			float mag = magnitude();
			x /= mag;
			y /= mag;
		}
	}

	float vec2::angle()
	{
		return atan2(-y, x);
	}

	//--------------------------------
	// member operators
	//--------------------------------
	vec2 vec2::operator+(vec2 other)
	{
		return vec2(x + other.x, y + other.y);
	}
	
	vec2 vec2::operator-(vec2 other)
	{
		return vec2(x - other.x, y - other.y);
	}
	
	vec2 vec2::operator*(float other)
	{
		return vec2(x * other, y * other);
	}
	
	vec2 vec2::operator/(float other)
	{
		return vec2(x / other, y / other);
	}
	
	vec2 vec2::operator=(vec2 other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}
	
	bool vec2::operator==(vec2 other)
	{
		return x == other.x && y == other.y;
	}
	
	bool vec2::operator!=(vec2 other)
	{
		return !(*this == other);
	}

	float & vec2::operator[](int index)
	{
		return data[index];
	}

	vec2 vec2::operator+=(vec2 other)
	{
		return *this = *this + other;
	}

	vec2 vec2::operator-=(vec2 other)
	{
		return *this = *this - other;
	}

	vec2 vec2::operator*=(float other)
	{
		return *this = *this * other;
	}

	vec2 vec2::operator/=(float other)
	{
		return *this = *this / other;
	}

	//--------------------------------
	// non-member operators
	//--------------------------------
	vec2 operator*(float me, vec2 other)
	{
		return vec2(me * other.x, me * other.y);
	}
	
	vec2 operator/(float me, vec2 other)
	{
		return vec2(me / other.x, me / other.y);
	}
	
	//--------------------------------
	// non-member functions
	//--------------------------------
	float dot(vec2 me, vec2 other)
	{
		return me.dot(other);
	}
	
	float magnitude(vec2 me)
	{
		return me.magnitude();
	}

	float magnitudeSquared(vec2 me)
	{
		return me.magnitudeSquared();
	}
	
	vec2 normalised(vec2 me)
	{
		return me.normalised();
	}
	
	void normalise(vec2 me)
	{
		me.normalise();
	}
}