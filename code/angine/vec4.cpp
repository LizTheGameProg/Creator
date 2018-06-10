#include "vec4.h"
#include "common (2).h"

namespace LML
{
	const vec4 vec4::Up = vec4::vec4(0.f, 1.f, 0.f);
	const vec4 vec4::Right = vec4::vec4(1.f, 0.f, 0.f);
	const vec4 vec4::Forward = vec4::vec4(0.f, 0.f, 1.f);

	vec4::vec4()
	{
		x = 0.f;
		y = 0.f;
		z = 0.f;
		w = 0.f;
	}

	vec4::vec4(float a_x, float a_y, float a_z, float a_w)
	{
		x = a_x;
		y = a_y;
		z = a_z;
		w = a_w;
	}

	vec4::vec4(vec4 & other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
	}

	vec4::~vec4()
	{
		x = 0.f;
		y = 0.f;
		z = 0.f;
		w = 0.f;
	}

	vec4 vec4::operator+(vec4 & other)
	{
		return vec4(x + other.x, y + other.y, z + other.z);
	}

	vec4 vec4::operator-(vec4 & other)
	{
		return vec4(x - other.x, y - other.y, z - other.z);
	}

	vec4 vec4::operator*(float other)
	{
		return vec4(x * other, y * other, z * other);
	}

	vec4 vec4::operator/(float other)
	{
		return vec4(x / other, y / other, z / other);
	}

	vec4 vec4::operator=(vec4 & other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	vec4 vec4::operator+=(vec4 & other)
	{
		*this = *this + other;
		return *this;
	}

	vec4 vec4::operator-=(vec4 & other)
	{
		*this = *this - other;
		return *this;
	}

	vec4 vec4::operator*=(float other)
	{
		*this = *this * other;
		return *this;
	}

	vec4 vec4::operator/=(float other)
	{
		*this = *this / other;
		return *this;
	}

	bool vec4::operator==(vec4 & other)
	{
		return	x == other.x &&
				y == other.y &&
				z == other.z;
	}

	float vec4::magnitude()
	{
		return LML::sqrt(x * x + y * y + z * z);
	}

	float vec4::length()
	{
		return magnitude();
	}

	vec4 vec4::normalised()
	{
		return *this / magnitude();
	}

	float vec4::dot(vec4 & other)
	{
		return x * other.x + y * other.y + z * other.z;
	}

	vec4 vec4::cross(vec4 & other)
	{
		return vec4(y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x);
	}
}