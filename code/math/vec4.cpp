#include "vec4.h"
#include "common.h"
#include "vec2.h"
#include "vec3.h"

namespace LML
{
	//--------------------------------
	// const static 'variables'
	//--------------------------------
	const vec4 vec4::Up = vec4(0.f, 1.f, 0.f, 0.f);
	const vec4 vec4::Right = vec4(1.f, 0.f, 0.f, 0.f);
	const vec4 vec4::Forward = vec4(0.f, 0.f, 1.f, 0.f);

	//--------------------------------
	// Constructors/Destructor
	//--------------------------------
	vec4::vec4()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}

	vec4::vec4(float a_all)
	{
		x = a_all;
		y = a_all;
		z = a_all;
		w = a_all;
	}

	vec4::vec4(vec3 a_vec, float a_w)
	{
		x = a_vec.x;
		y = a_vec.y;
		z = a_vec.z;
		w = a_w;
		if(w >= 1.f)
			w = 1.f;
		if(w < 0.f)
			w = 1.f;
	}

	vec4::vec4(vec2 a_vec, float a_z, float a_w)
	{
		x = a_vec.x;
		y = a_vec.y;
		z = a_z;
		w = a_w;
		if(w >= 1.f)
			w = 1.f;
		if(w < 0.f)
			w = 1.f;
	}

	vec4::vec4(float a_x, float a_y, float a_z, float a_w)
	{
		x = a_x;
		y = a_y;
		z = a_z;
		w = a_w;
		if(w > 1.f)
			w = 1.f;
		if(w < 0.f)
			w = 1.f;
	}

	vec4::~vec4()
	{

	}

	//--------------------------------
	// Utility
	//--------------------------------
	float vec4::dot(vec4 other)
	{
		return x * other.x + y * other.y + z * other.z;
	}

	vec4 vec4::cross(vec4 other)
	{
		vec4 cross;
		cross.x = y * other.z - z * other.y;
		cross.y = z * other.x - x * other.z;
		cross.z = x * other.y - y * other.x;
		return cross;
	}

	float vec4::magnitude()
	{
		return sqrt(x * x + y * y + z * z);
	}

	float vec4::magnitudeSquared()
	{
		return x * x + y * y + z * z;
	}

	vec4 vec4::normalised()
	{
		vec4 norm;
		if(magnitudeSquared() != 0.f)
		{
			float mag = magnitude();
			norm.x = x / mag;
			norm.y = y / mag;
			norm.z = z / mag;
		}
		return norm;
	}

	void vec4::normalise()
	{
		if(magnitudeSquared() != 0.f)
		{
			float mag = magnitude();
			x /= mag;
			y /= mag;
			z /= mag;
		}
	}
	
	//--------------------------------
	// operators
	//--------------------------------
	vec4 vec4::operator+(vec4 other)
	{
		return vec4(x + other.x, y + other.y, z + other.z, w + other.w);
	}

	vec4 vec4::operator-(vec4 other)
	{
		return vec4(x - other.x, y - other.y, z - other.z, w > other.w ? w : other.w);
	}

	vec4 vec4::operator*(float other)
	{
		return vec4(x * other, y * other, z * other, w);
	}

	vec4 vec4::operator/(float other)
	{
		return vec4(x / other, y / other, z / other, w);
	}

	vec4 vec4::operator=(vec4 other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
		return *this;
	}

	bool vec4::operator==(vec4 other)
	{
		return x == other.x && y == other.y && z == other.z;
	}

	bool vec4::operator!=(vec4 other)
	{
		return !(*this == other);
	}

	float & vec4::operator[](int index)
	{
		return data[index];
	}

	//--------------------------------
	// non-member operators
	//--------------------------------
	vec4 operator*(float me, vec4 other)
	{
		return vec4(me * other.x, me * other.y, me * other.z, other.w);
	}

	vec4 operator/(float me, vec4 other)
	{
		return vec4(me / other.x, me / other.y, me / other.z, other.w);
	}

	//--------------------------------
	// non-member functions
	//--------------------------------
	float dot(vec4 me, vec4 other)
	{
		return me.dot(other);
	}

	float magnitude(vec4 me)
	{
		return me.magnitude();
	}

	float magnitudeSquared(vec4 me)
	{
		return me.magnitudeSquared();
	}

	vec4 normalised(vec4 me)
	{
		return me.normalised();
	}

	void normalise(vec4 me)
	{
		me.normalise();
	}

}