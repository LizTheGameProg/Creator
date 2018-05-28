#pragma once
#include "vec2.h"
#include <iostream>

void vec2ConstructorVOID()
{
	LML::vec2 test;
	if(test.x == 0.f && test.y == 0.f)
	{

	}
	else
	{
		printf("vec2 constructor XYZ = 0 test failed\n");
	}
}

void vec2ConstructorFLOAT()
{
	LML::vec2 test(1);
	if(test.x == 1.f && test.y == 1.f)
	{

	}
	else
	{
		printf("vec2 constructor XY = float test failed\n");
	}
}

void vec2ConstructorFLOATFLOAT()
{
	LML::vec2 test(3, 4);
	if(test.x == 3.f && test.y == 4.f)
	{

	}
	else
	{
		printf("vec2 constructor X = float, Y = float test failed\n");
	}
}

void vec2dot()
{
	LML::vec2 a(15, 5);
	LML::vec2 b(1, 9);

	if(a.dot(b) == 60.f)
	{

	}
	else
	{
		printf("vec2 dot test failed\n");
	}
}

void vec2Magnitude()
{
	LML::vec2 test(3, 4);
	float mag = test.magnitude();
	if(mag == 5.f)
	{

	}
	else
	{
		printf("vec2 mag test failed\n");
	}
}

void vec2MagnitudeSquared()
{
	LML::vec2 test(3, 4);
	float magSquared = test.magnitudeSquared();
	if(magSquared == 25.f)
	{

	}
	else
	{
		printf("vec2 magSquared test failed\n");
	}
}

void vec2Normalised()
{
	LML::vec2 test(3, 4);
	LML::vec2 normalised = test.normalised();
	if(normalised.x == 3.f / 5.f && normalised.y == 4.f / 5.f)
	{

	}
	else
	{
		std::cout << normalised.x << " " << normalised.y << std::endl;
		printf("vec2 normalised test failed\n");
	}
}

void vec2Normalise()
{
	LML::vec2 test(3, 4);
	test.normalise();
	if(test.x == 3.f / 5.f && test.y == 4.f / 5.f)
	{

	}
	else
	{
		printf("vec2 normalise test failed\n");
	}
}

void vec2OperatorPlus()
{
	LML::vec2 a(3, 4);
	LML::vec2 b(7, 6);
	LML::vec2 c = a + b;
	if(c.x == 10.f && c.y == 10.f)
	{

	}
	else
	{
		printf("vec2 operator+ test failed\n");
	}
}

void vec2OperatorMinus()
{
	LML::vec2 a(3, 4);
	LML::vec2 b(7, 6);
	LML::vec2 c = a - b;
	if(c.x == -4.f && c.y == -2.f)
	{

	}
	else
	{
		printf("vec2 operator- test failed\n");
	}
}

void vec2OperatorTimesScalar()
{
	{
		LML::vec2 a(3, 4);
		float b = 3.f;
		LML::vec2 c = a * b;
		if(c.x == 9.f && c.y == 12.f)
		{

		}
		else
		{
			printf("vec2 operator * float test failed\n");
		}
	}
	{
		LML::vec2 a(3, 4);
		float b = 3.f;
		LML::vec2 c = b * a;
		if(c.x == 9.f && c.y == 12.f)
		{

		}
		else
		{
			printf("vec2 operator * float test failed\n");
		}
	}
}

void vec2OperatorDivideScalar()
{
	{
		LML::vec2 a(3, 4);
		float b = 3.f;
		LML::vec2 c = a / b;
		if(c.x == 3.f / 3.f && c.y == 4.f / 3.f)
		{

		}
		else
		{
			printf("vec2 operator * vec2 * float test failed\n");
		}
	}
	{
		LML::vec2 a(3, 4);
		float b = 3.f;
		LML::vec2 c = b / a;
		if(c.x == 3.f / 3.f && c.y == 3.f / 4.f)
		{

		}
		else
		{
			printf("vec2 operator * float * vec2 test failed\n");
		}
	}
}

void vec2OperatorEquals()
{
	LML::vec2 test(3, 4);
	LML::vec2 copy = test;
	if(copy.x == 3 && copy.y == 4.f)
	{

	}
	else
	{
		printf("vec2 equals test failed\n");
	}
}

void vec2OperatorIsEqual()
{
	LML::vec2 test(3, 4);
	LML::vec2 copy = test;
	if(copy == test)
	{

	}
	else
	{
		printf("vec2 isEquals test failed\n");
	}
}

void vec2OperatorNotEqual()
{
	LML::vec2 test(3, 4);
	LML::vec2 copy = test;
	copy.x += 1.f;
	if(copy != test)
	{

	}
	else
	{
		printf("vec2 NotEqual test failed\n");
	}
}

void vec2OperatorSubscript()
{
	LML::vec2 test(3, 4);
	if(test[0] == 3.f && test[1] == 4.f)
	{

	}
	else
	{
		printf("vec2 operator test failed\n");
	}
}