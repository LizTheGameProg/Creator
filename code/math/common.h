#pragma once

namespace LML
{
	/*
	abs
	sin
	cos
	tan
	asin
	acos
	atan
	min
	max
	clamp
	sqrt
	radians
	degrees

	pi
	*/

	float degrees(float radians);
	float radians(float degrees);

	float cos(float angle);
	float sin(float angle);
	float tan(float angle);

	float sqrt(float x);

	float acos(float x);
	float asin(float x);
	float atan(float x);
	float atan2(float y, float x);

	float abs(float value);
	float clamp(float min, float max, float value);

	// float lerp(float start, float end, float time);

	static float PI = 3.1415926f;
}