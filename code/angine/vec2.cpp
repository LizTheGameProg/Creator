#include "vec2.h"
#include "common (2).h"

namespace LML
{
	const vec2 vec2::Up = vec2(0.f, 1.f);
	const vec2 vec2::Right = vec2(1.f, 0.f);

	vec2::vec2()
	{
		x = 0.f;
		y = 0.f;
	}

	vec2::vec2(float a_x, float a_y)
	{
		x = a_x;
		y = a_y;
	}

	vec2::vec2(vec2 & other)
	{
		x = other.x;
		y = other.y;
	}

	vec2::~vec2()
	{
		x = 0.f;
		y = 0.f;
	}

	vec2 vec2::operator+(vec2 & other)
	{
		return vec2(x + other.x, y + other.y);
	}

	vec2 vec2::operator-(vec2 & other)
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

	vec2 vec2::operator=(vec2 & other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}

	vec2 vec2::operator+=(vec2 & other)
	{
		*this = *this + other;
		return *this;
	}

	vec2 vec2::operator-=(vec2 & other)
	{
		*this = *this - other;
		return *this;
	}

	vec2 vec2::operator*=(float other)
	{
		*this = *this * other;
		return *this;
	}

	vec2 vec2::operator/=(float other)
	{
		*this = *this / other;
		return *this;
	}

	bool vec2::operator==(vec2 & other)
	{
		return x == other.x && y == other.y;
	}

	float vec2::magnitude()
	{
		return sqrt(x * x + y * y);
	}

	float vec2::length()
	{
		return magnitude();
	}

	vec2 vec2::normalised()
	{
		return *this / magnitude();
	}

	float vec2::dot(vec2 & other)
	{
		return x * other.x + y * other.y;
	}
}