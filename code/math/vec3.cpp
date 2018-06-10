#include "vec3.h"
#include "vec2.h"
#include "common (2).h"

namespace LML
{
	const vec3 vec3::Up = vec3(0.f, 1.f, 0.f);
	const vec3 vec3::Right = vec3(1.f, 0.f, 0.f);
	const vec3 vec3::Forward = vec3(0.f, 0.f, 1.f);

	//--------------------------------
	// Constructors/Destructor
	//--------------------------------
	vec3::vec3()
	{
		x = 0.f;
		y = 0.f;
		z = 0.f;
	}

	vec3::vec3(float a_all)
	{
		x = a_all;
		y = a_all;
		z = a_all;
	}
	
	vec3::vec3(vec2 a_vec, float a_z)
	{
		x = a_vec.x;
		y = a_vec.y;
		z = a_z;
	}

	vec3::vec3(float a_x, float a_y, float a_z)
	{
		x = a_x;
		y = a_y;
		z = a_z;
	}

	vec3::~vec3()
	{

	}

	//--------------------------------
	// Utility
	//--------------------------------
	float vec3::dot(vec3 other)
	{
		return x * other.x + y * other.y + z * other.z;
	}

	vec3 vec3::cross(vec3 other)
	{
		vec3 cross;
		cross.x = y * other.z - z * other.y;
		cross.y = z * other.x - x * other.z;
		cross.z = x * other.y - y * other.x;
		return cross;
	}

	float vec3::magnitude()
	{
		return sqrt(x * x + y * y + z * z);
	}

	float vec3::magnitudeSquared()
	{
		return x * x + y * y + z * z;
	}

	vec3 vec3::normalised()
	{
		vec3 norm;
		if(magnitudeSquared() != 0.f)
		{
			float mag = magnitude();
			norm.x = x / mag;
			norm.y = y / mag;
			norm.z = z / mag;
		}
		return norm;
	}

	void vec3::normalise()
	{
		if(magnitudeSquared() != 0.f)
		{
			float mag = magnitude();
			x /= mag;
			y /= mag;
			z /= mag;
		}
	}

	vec2 vec3::xy()
	{
		return vec2(x, y);
	}

	//--------------------------------
	// member operators
	//--------------------------------
	vec3 vec3::operator+(vec3 other)
	{
		return vec3(x + other.x, y + other.y, z + other.z);
	}

	vec3 vec3::operator-(vec3 other)
	{
		return vec3(x - other.x, y - other.y, z - other.z);
	}

	vec3 vec3::operator*(float other)
	{
		return vec3(x * other, y * other, z * other);
	}

	vec3 vec3::operator/(float other)
	{
		return vec3(x / other, y / other, z / other);
	}

	vec3 vec3::operator=(vec3 other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	bool vec3::operator==(vec3 other)
	{
		return x == other.x && y == other.y && z == other.z;
	}

	bool vec3::operator!=(vec3 other)
	{
		return !(*this == other);
	}

	float & vec3::operator[] (int index)
	{
		return data[index];
	}

	//--------------------------------
	// non-member operators
	//--------------------------------
	vec3 operator*(float me, vec3 other)
	{
		return vec3(me * other.x, me * other.y,  me * other.z);
	}

	vec3 operator/(float me, vec3 other)
	{
		return vec3(me / other.x, me / other.y,  me / other.z);
	}

	//--------------------------------
	// non-member functions
	//--------------------------------
	float dot(vec3 me, vec3 other)
	{
		return me.dot(other);
	}

	float magnitude(vec3 me)
	{
		return me.magnitude();
	}

	float magnitudeSquared(vec3 me)
	{
		return me.magnitudeSquared();
	}

	vec3 normalised(vec3 me)
	{
		return me.normalised();
	}

	void normalise(vec3 me)
	{
		return me.normalise();
	}
}