#include "vec3.h"
#include "common.h"

namespace LML
{
	const vec3 vec3::Up = vec3::vec3(0.f, 1.f, 0.f);
	const vec3 vec3::Right = vec3::vec3(1.f, 0.f, 0.f);
	const vec3 vec3::Forward = vec3::vec3(0.f, 0.f, 1.f);

	vec3::vec3()
	{
		x = 0.f;
		y = 0.f;
		z = 0.f;
	}

	vec3::vec3(float a_x, float a_y, float a_z)
	{
		x = a_x;
		y = a_y;
		z = a_z;
	}

	vec3::vec3(vec3 & other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}

	vec3::~vec3()
	{
		x = 0.f;
		y = 0.f;
		z = 0.f;
	}

	vec3 vec3::operator+(vec3 & other)
	{
		return vec3(x + other.x, y + other.y, z + other.z);
	}

	vec3 vec3::operator-(vec3 & other)
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

	vec3 vec3::operator=(vec3 & other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	vec3 vec3::operator+=(vec3 & other)
	{
		*this = *this + other;
		return *this;
	}

	vec3 vec3::operator-=(vec3 & other)
	{
		*this = *this - other;
		return *this;
	}

	vec3 vec3::operator*=(float other)
	{
		*this = *this * other;
		return *this;
	}

	vec3 vec3::operator/=(float other)
	{
		*this = *this / other;
		return *this;
	}

	bool vec3::operator==(vec3 & other)
	{
		return	x == other.x &&
			y == other.y &&
			z == other.z;
	}

	float& vec3::operator[](int index)
	{
		switch(index)
		{
		case 0:
			return x;
			break;
		case 1:
			return y;
			break;
		case 2:
			return z;
			break;
		default:
			break;
		}
	}

	float vec3::magnitude()
	{
		return LML::sqrt(x * x + y * y + z * z);
	}

	float vec3::length()
	{
		return magnitude();
	}

	vec3 vec3::normalised()
	{
		return *this / magnitude();
	}

	float vec3::dot(vec3 & other)
	{
		return x * other.x + y * other.y + z * other.z;
	}

	vec3 vec3::cross(vec3 & other)
	{
		return vec3(y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x);
	}
}