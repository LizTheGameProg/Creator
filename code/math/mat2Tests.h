#pragma once
#include "mat2.h"
#include <iostream>

void mat2ConstructorVOID()
{
	LML::mat2 test;
	if(test.data[0] == 1.f && test.data[1] == 0.f && test.data[2] == 0.f && test.data[3] == 1.f)
	{

	}
	else
	{
		printf("mat2 constructor VOID test failed\n");
	}
}

void mat2ConstructorFLOATFLOATFLOATFLOAT()
{
	LML::mat2 test(1.f, 2.f, 3.f, 4.f);
	if(test.data[0] == 1.f && test.data[1] == 2.f && test.data[2] == 3.f && test.data[3] == 4.f)
	{

	}
	else
	{
		printf("mat2 constructor FLOATFLOATFLOATFLOAT test failed\n");
	}
}

void mat2Transposed()
{
	LML::mat2 test(1.f, 2.f, 3.f, 4.f);
	test = test.transposed();
	if(test.data[0] == 1.f && test.data[1] == 3.f && test.data[2] == 2.f && test.data[3] == 4.f)
	{

	}
	else
	{
		printf("mat2 transposed test failed\n");
	}
}

void mat2Inverse()
{
	LML::mat2 test(1.f, 2.f, 3.f, 4.f);
	test = test.inverse();
	if(test.data[0] == -1/2.f && test.data[1] == -2/2.f && test.data[2] == -3/2.f && test.data[3] == -4/2.f)
	{

	}	
	else
	{
		printf("mat2 inverse test failed\n");
	}
}

void mat2Determinant()
{
	LML::mat2 test(1.f, 2.f, 3.f, 4.f);
	float det = test.determinant();
	// det = 1 * 4 - 2 * 3
	// det = -2
	if(det == -2.f)
	{

	}
	else
	{
		printf("mat2 determinant test failed\n");
	}
}

void mat2OperatorTimesFLOAT()
{
	LML::mat2 test(1.f, 2.f, 3.f, 4.f);
	test = test * 2.f;
	if(test.data[0] == 2.f && test.data[1] == 4.f && test.data[2] == 6.f && test.data[3] == 8.f)
	{

	}
	else
	{
		printf("mat2 operator times float test failed\n");
	}
}

void mat2OperatorTimesVEC2()
{
	LML::mat2 a(1.f, 2.f, 3.f, 4.f);
	LML::vec2 b(5.f, 6.f);
	LML::vec2 c = a * b;
	if(c.x == 17.f && c.y == 39.f)
	{

	}
	else
	{
		printf("mat2 operator times vec2 test failed\n");
	}
}

void mat2OperatorTimesMAT2()
{
	LML::mat2 a(1.f, 2.f, 3.f, 4.f);
	LML::mat2 b(5.f, 6.f, 7.f, 8.f);
	LML::mat2 c = a * b;
	if(c[0].x == 19.f && c[0].y == 22.f && c[1].x == 43.f && c[1].y == 50.f)
	{

	}
	else
	{
		printf("mat2 operator times mat2 test failed\n");
	}
}

void mat2OperatorSubscript()
{
	LML::mat2 test(1.f, 2.f, 3.f, 4.f);
	if(test[0].x == 1.f && test[0].y == 2.f && test[1].x == 3.f && test[1].y == 4.f)
	{

	}
	else
	{
		printf("mat2 operator subscript test failed\n");
	}
}

void mat2OperatorEquals()
{
	LML::mat2 test(1.f, 2.f, 3.f, 4.f);
	LML::mat2 copy = test;
	if(copy[0].x == 1.f && copy[0].y == 2.f && copy[1].x == 3.f && copy[1].y == 4.f)
	{

	}
	else
	{
		printf("mat2 operator equals test failed\n");
	}
}

void mat2OperatorIsEqual()
{
	LML::mat2 test(1.f, 2.f, 3.f, 4.f);
	LML::mat2 copy = test;
	if(copy == test)
	{

	}
	else
	{
		printf("mat2 operator is equal test failed\n");
	}
}

void mat2OperatorNotEqual()
{
	LML::mat2 test(1.f, 2.f, 3.f, 4.f);
	LML::mat2 copy = test;
	copy[3] = 1.f;
	if(copy != test)
	{

	}
	else
	{
		printf("mat2 operator is equal test failed\n");
	}
}

void mat2OperatorFLOATtimesMAT2()
{
	LML::mat2 test(1.f, 2.f, 3.f, 4.f);
	test = 2.f * test;
	if(test.data[0] == 2.f && test.data[1] == 4.f && test.data[2] == 6.f && test.data[3] == 8.f)
	{

	}
	else
	{
		printf("mat2 operator times float test failed\n");
	}
}