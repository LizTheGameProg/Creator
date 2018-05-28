#include "common.h"
#include <math.h>

namespace ANGINE
{
	float sqrt(float x)
	{
		return (float)::sqrt(x);
	}

	float sin(float x)
	{
		return (float)::sin(x);
	}

	float cos(float x)
	{
		return (float)::cos(x);
	}

	float tan(float x)
	{
		return (float)::tan(x);
	}

	float asin(float x)
	{
		return (float)::asin(x);
	}

	float acos(float x)
	{
		return (float)::acos(x);
	}

	float atan(float x)
	{
		return (float)::atan(x);
	}

	float degrees(float radians)
	{
		return radians * (180.f / (float) PI);
	}

	float radians(float degrees)
	{
		return degrees * ((float) PI / 180.f);
	}
}