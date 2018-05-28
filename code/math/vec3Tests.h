#pragma once
#include "vec3.h"
#include "vec2.h"
#include <iostream>

void vec3ConstructorVOID()
{
	LML::vec3 test;
	if(test.x == 0.f && test.y == 0.f && test.z == 0.f)
	{

	}
	else
	{
		printf("vec3 constructor XYZ = 0 test failed\n");
	}
}

void vec3ConstructorFLOAT()
{
	LML::vec3 test(1);
	if(test.x == 1.f && test.y == 1.f && test.z == 1.f)
	{

	}
	else
	{
		printf("vec3 constructor XYZ = float test failed\n");
	}
}

void vec3ConstructorVEC2FLOAT()
{
	LML::vec3 test(LML::vec2(3, 4), 5);
	if(test.x == 3.f && test.y == 4.f && test.z == 5.f)
	{

	}
	else
	{
		printf("vec3 constructor XY = vec2, Z = float test failed\n");
	}
}

void vec3ConstructorFLOATFLOATFLOAT()
{
	LML::vec3 test(3, 4, 5);
	if(test.x == 3.f && test.y == 4.f && test.z == 5.f)
	{

	}
	else
	{
		printf("vec3 constructor X = float, Y = float, Z = float test failed\n");
	}
}

void vec3dot()
{
	LML::vec3 a(3, 4, 5);
	LML::vec3 b(6, 7, 8);

	if(a.dot(b) == b.dot(a))
	{

	}
	else
	{
		printf("vec3 dot test failed\n");
	}
}

void vec3cross()
{
	LML::vec3 a(3, 4, 5);
	LML::vec3 b(8, 7, 6);
	LML::vec3 c = a.cross(b);
	if(c.x == -11.f && c.y == 22.f && c.z == -11.f)
	{

	}
	else
	{
		printf("vec3 cross test failed\n");
	}
}

void vec3Magnitude()
{
	LML::vec3 test(3, 4, 5);
	float mag = test.magnitude();
	if(mag == 7.0710678f)
	{

	}
	else
	{
		printf("vec3 mag test failed\n");
	}
}

void vec3MagnitudeSquared()
{
	LML::vec3 test(3, 4, 5);
	float magSquared = test.magnitudeSquared();
	if(magSquared == 7.0710678f * 7.0710678f)
	{

	}
	else
	{
		printf("vec3 magSquared test failed\n");
	}
}

void vec3Normalised()
{
	LML::vec3 test(3, 4, 5);
	LML::vec3 normalised = test.normalised();
	if(normalised.x == 3.f / 7.0710678f && normalised.y == 4.f / 7.0710678f && normalised.z == 5.f / 7.0710678f)
	{

	}
	else
	{
		std::cout << normalised.x << " " << normalised.y << std::endl;
		printf("vec3 normalised test failed\n");
	}
}

void vec3Normalise()
{
	LML::vec3 test(3, 4, 5);
	test.normalise();
	if(test.x == 3.f / 7.0710678f && test.y == 4.f / 7.0710678f && test.z == 5.f / 7.0710678f)
	{

	}
	else
	{
		printf("vec3 normalise test failed\n");
	}
}

void vec3OperatorPlus()
{
	LML::vec3 a(3, 4, 5);
	LML::vec3 b(7, 6, 8);
	LML::vec3 c = a + b;
	if(c.x == 10.f && c.y == 10.f && c.z == 13.f)
	{

	}
	else
	{
		printf("vec3 operator+ test failed\n");
	}
}

void vec3OperatorMinus()
{
	LML::vec3 a(3, 4, 5);
	LML::vec3 b(7, 6, 8);
	LML::vec3 c = a - b;
	if(c.x == -4.f && c.y == -2.f && c.z == -3.f)
	{

	}
	else
	{
		printf("vec3 operator- test failed\n");
	}
}

void vec3OperatorTimesScalar()
{
	{
		LML::vec3 a(3, 4, 5);
		float b = 3.f;
		LML::vec3 c = a * b;
		if(c.x == 9.f && c.y == 12.f && c.z == 15.f)
		{

		}
		else
		{
			printf("vec3 operator * float test failed\n");
		}
	}
	{
		LML::vec3 a(3, 4, 5);
		float b = 3.f;
		LML::vec3 c = b * a;
		if(c.x == 9.f && c.y == 12.f && c.z == 15.f)
		{

		}
		else
		{
			printf("vec3 operator * float test failed\n");
		}
	}
}

void vec3OperatorDivideScalar()
{
	{
		LML::vec3 a(3, 4, 5);
		float b = 3.f;
		LML::vec3 c = a / b;
		if(c.x == 3.f / 3.f && c.y == 4.f / 3.f && c.z == 5.f / 3.f)
		{

		}
		else
		{
			printf("vec3 operator * vec3 * float test failed\n");
		}
	}
	{
		LML::vec3 a(3, 4, 5);
		float b = 3.f;
		LML::vec3 c = b / a;
		if(c.x == 3.f / 3.f && c.y == 3.f / 4.f && c.z == 3.f / 5.f)
		{

		}
		else
		{
			printf("vec3 operator * float * vec3 test failed\n");
		}
	}
}

void vec3OperatorEquals()
{
	LML::vec3 test(3, 4, 5);
	LML::vec3 copy = test;
	if(copy.x == 3.f && copy.y == 4.f && copy.z == 5.f)
	{

	}
	else
	{
		printf("vec3 equals test failed\n");
	}
}

void vec3OperatorIsEqual()
{
	LML::vec3 test(3, 4, 5);
	LML::vec3 copy = test;
	if(copy == test)
	{

	}
	else
	{
		printf("vec3 isEquals test failed\n");
	}
}

void vec3OperatorNotEqual()
{
	LML::vec3 test(3, 4, 5);
	LML::vec3 copy = test;
	copy.x += 1.f;
	if(copy != test)
	{

	}
	else
	{
		printf("vec3 NotEqual test failed\n");
	}
}

void vec3OperatorSubscript()
{
	LML::vec3 test(3, 4, 5);
	if(test[0] == 3.f && test[1] == 4.f && test[2] == 5.f)
	{

	}
	else
	{
		printf("vec3 operator test failed\n");
	}
}