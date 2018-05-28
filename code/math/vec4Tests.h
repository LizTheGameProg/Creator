#pragma once
#include "vec4.h"
#include "vec2.h"
#include <iostream>

void vec4ConstructorVOID()
{
	LML::vec4 test;
	if(test.x == 0.f && test.y == 0.f && test.z == 0.f && test.w == 0.f)
	{

	}
	else
	{
		printf("vec4 constructor XYZ = 0 test failed\n");
	}
}

void vec4ConstructorFLOAT()
{
	LML::vec4 test(1);
	if(test.x == 1.f && test.y == 1.f && test.z == 1.f && test.w == 1.f)
	{

	}
	else
	{
		printf("vec4 constructor XYZW = 0 test failed\n");
	}
}

void vec4ConstructorVEC3FLOAT()
{
	LML::vec4 test(LML::vec3(3, 4, 5), 1);
	if(test.x == 3.f && test.y == 4.f && test.z == 5.f && test.w == 1.f)
	{

	}
	else
	{
		printf("vec4 constructor XYZ = vec3, W = float test failed\n");
	}
}

void vec4ConstructorVEC2FLOATFLOAT()
{
	LML::vec4 test(LML::vec2(3, 4), 5, 1);
	if(test.x == 3.f && test.y == 4.f && test.z == 5.f && test.w == 1.f)
	{

	}
	else
	{
		printf("vec4 constructor XY = vec2, Z = float, W = float test failed\n");
	}
}

void vec4ConstructorFLOATFLOATFLOATFLOAT()
{
	LML::vec4 test(3, 4, 5, 1);
	if(test.x == 3.f && test.y == 4.f && test.z == 5.f && test.w == 1.f)
	{

	}
	else
	{
		printf("vec4 constructor X = a_x, Y = a_y, Z = a_z test failed\n");
	}
}

void vec4dot()
{
	LML::vec4 a(3, 4, 5, 1);
	LML::vec4 b(6, 7, 8, 1);

	if(a.dot(b) == b.dot(a))
	{

	}
	else
	{
		printf("vec4 dot test failed\n");
	}
}


void vec4cross()
{
	LML::vec4 a(3, 4, 5, 1);
	LML::vec4 b(8, 7, 6, 1);
	LML::vec4 c = a.cross(b);
	if(c.x == -11.f && c.y == 22.f && c.z == -11.f)
	{

	}
	else
	{
		printf("vec4 cross test failed\n");
	}
}

void vec4Magnitude()
{
	LML::vec4 test(3, 4, 5, 1);
	float mag = test.magnitude();
	if(mag == 7.0710678f)
	{

	}
	else
	{
		printf("vec4 mag test failed\n");
	}
}

void vec4MagnitudeSquared()
{
	LML::vec4 test(3, 4, 5, 1);
	float magSquared = test.magnitudeSquared();
	if(magSquared == 7.0710678f * 7.0710678f)
	{

	}
	else
	{
		printf("vec4 magSquared test failed\n");
	}
}

void vec4Normalised()
{
	LML::vec4 test(3, 4, 5, 1);
	LML::vec4 normalised = test.normalised();
	if(normalised.x == 3.f / 7.0710678f && normalised.y == 4.f / 7.0710678f && normalised.z == 5.f / 7.0710678f)
	{

	}
	else
	{
		std::cout << normalised.x << " " << normalised.y << std::endl;
		printf("vec4 normalised test failed\n");
	}
}

void vec4Normalise()
{
	LML::vec4 test(3, 4, 5, 1);
	test.normalise();
	if(test.x == 3.f / 7.0710678f && test.y == 4.f / 7.0710678f && test.z == 5.f / 7.0710678f)
	{

	}
	else
	{
		printf("vec4 normalise test failed\n");
	}
}

void vec4OperatorPlus()
{
	LML::vec4 a(3, 4, 5, 1);
	LML::vec4 b(7, 6, 8, 1);
	LML::vec4 c = a + b;
	if(c.x == 10.f && c.y == 10.f && c.z == 13.f && c.w == 1.f)
	{

	}
	else
	{
		printf("vec4 operator+ test failed\n");
	}
}

void vec4OperatorMinus()
{
	LML::vec4 a(3, 4, 5, 1);
	LML::vec4 b(7, 6, 8, 1);
	LML::vec4 c = a - b;
	if(c.x == -4.f && c.y == -2.f && c.z == -3.f && c.w == 1.f)
	{

	}
	else
	{
		printf("vec4 operator- test failed\n");
	}
}

void vec4OperatorTimesScalar()
{
	{
		LML::vec4 a(3, 4, 5, 1);
		float b = 3.f;
		LML::vec4 c = a * b;
		if(c.x == 9.f && c.y == 12.f && c.z == 15.f && c.w == 1.f)
		{

		}
		else
		{
			printf("vec4 operator * float test failed\n");
		}
	}
	{
		LML::vec4 a(3, 4, 5, 1);
		float b = 3.f;
		LML::vec4 c = b * a;
		if(c.x == 9.f && c.y == 12.f && c.z == 15.f && c.w == 1.f)
		{

		}
		else
		{
			printf("vec4 operator * float test failed\n");
		}
	}
}

void vec4OperatorDivideScalar()
{
	{
		LML::vec4 a(3, 4, 5, 1);
		float b = 3.f;
		LML::vec4 c = a / b;
		if(c.x == 3.f / 3.f && c.y == 4.f / 3.f && c.z == 5.f / 3.f && c.w == 1.f)
		{

		}
		else
		{
			printf("vec4 operator * vec4 * float test failed\n");
		}
	}
	{
		LML::vec4 a(3, 4, 5, 1);
		float b = 3.f;
		LML::vec4 c = b / a;
		if(c.x == 3.f / 3.f && c.y == 3.f / 4.f && c.z == 3.f / 5.f && c.w == 1.f)
		{

		}
		else
		{
			printf("vec4 operator * float * vec4 test failed\n");
		}
	}
}

void vec4OperatorEquals()
{
	LML::vec4 test(3, 4, 5, 1);
	LML::vec4 copy = test;
	if(copy.x == 3.f && copy.y == 4.f && copy.z == 5.f && copy.w == 1.f)
	{

	}
	else
	{
		printf("vec4 equals test failed\n");
	}
}

void vec4OperatorIsEqual()
{
	LML::vec4 test(3, 4, 5, 1);
	LML::vec4 copy = test;
	if(copy == test)
	{

	}
	else
	{
		printf("vec4 isEquals test failed\n");
	}
}

void vec4OperatorNotEqual()
{
	LML::vec4 test(3, 4, 5, 1);
	LML::vec4 copy = test;
	copy.x += 1.f;
	if(copy != test)
	{

	}
	else
	{
		printf("vec4 NotEqual test failed\n");
	}
}

void vec4OperatorSubscript()
{
	LML::vec4 test(3, 4, 5, 1);
	if(test[0] == 3.f && test[1] == 4.f && test[2] == 5.f && test[3] == 1.f)
	{

	}
	else
	{
		printf("vec4 operator test failed\n");
	}
}