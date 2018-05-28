#include "common.h"
#include <math.h>

namespace LML
{
	float degrees(float radians)
	{
		return (radians / PI) * 180.f;
	}

	float radians(float degrees)
	{
		return (degrees / 180.f) * PI;
	}

	float cos(float a_angle)
	{
		return (float)::cos(a_angle);
	}

	float sin(float a_angle)
	{
		return (float)::sin(a_angle);
	}

	float tan(float a_angle)
	{
		return (float)::tan(a_angle);
	}

	float sqrt(float a_x)
	{
		return (float)::sqrt(a_x);
	}

	float acos(float a_x)
	{
		return (float)::acos(a_x);
	}

	float asin(float a_x)
	{
		return (float)::asin(a_x);
	}

	float atan(float a_x)
	{
		return (float)::atan(a_x);
	}
	
	float atan2(float a_y, float a_x)
	{
		return (float)::atan2(a_y, a_x);
	}

	float abs(float a_value)
	{
		return (float)::abs((int)a_value);
	}

	float clamp(float a_min, float a_max, float a_value)
	{
		if(a_value < a_min)
			a_value = a_min;
		else if(a_value > a_max)
			a_value = a_max;
		return a_value;
	}
}