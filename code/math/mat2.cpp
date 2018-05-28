#include "mat2.h"
#include <iostream>

namespace LML
{
	//--------------------------------
	// Constructors/Destructor
	//--------------------------------
	mat2::mat2()
	{
		// Set everything to 0
		m[0] = vec2();
		m[1] = vec2();

		// Set up the identity matrix (diagonals to 1)
		m[0][0] = 1.f;
		m[1][1] = 1.f;
	}

	mat2::mat2(float m00, float m01, float m10, float m11)
	{
		m[0][0] = m00;
		m[0][1] = m01;
		m[1][0] = m10;
		m[1][1] = m11;
	}

	mat2::~mat2()
	{

	}

	//--------------------------------
	// Utility
	//--------------------------------
	mat2 mat2::transposed()
	{
		mat2 transposedMatrix;
		unsigned int matrixSize = 2;
		for(unsigned int i = 0; i < matrixSize; i++)
		{
			for(unsigned int j = 0; j < matrixSize; j++)
			{
				transposedMatrix[j][i] = m[i][j];
			}
		}
		return transposedMatrix;
	}

	mat2 mat2::inverse()
	{
		// inverse is 1/det * matrix;
		return (1.f / determinant()) * *this;
	}

	float mat2::determinant()
	{
		// determinant = ad - bc
		//	|a b|
		//	|c d|
		return (m[0][0] * m[1][1]) - (m[0][1] * m[1][0]);
	}

	void mat2::printToConsole()
	{
		printf("|%f %f|\n|%f %f|\n", m[0][0], m[0][1], m[1][0], m[1][1]);
	}

	//--------------------------------
	// operators
	//--------------------------------
	mat2 mat2::operator*(float scalar)
	{
		return mat2(m[0][0] * scalar, m[0][1] * scalar, m[1][0] * scalar, m[1][1] * scalar);
	}

	vec2 mat2::operator*(vec2 other)
	{
		/*
		|1 2|
		|3 4|
		  *
		|5|
		|6|
		  =
		|a|
		|b|

		a = 1 * 5 + 2 * 6;
		b = 3 * 5 + 4 * 6;
		*/
		return vec2(m[0][0] * other.x + m[0][1] * other.y, m[1][0] * other.x + m[1][1] * other.y);
	}

	mat2 mat2::operator*(mat2 other)
	{
		mat2 matrix;

		/*
		|1 2|
		|3 4|
		  *
		|5 7|
		|6 8|
		  =
		|a b|
		|c d|

		a = 1 * 5 + 2 * 6;
		b = 1 * 7 + 2 * 8;
		c = 3 * 5 + 4 * 6;
		d = 3 * 7 + 4 * 8;

		*/

		//matrix[0][0] = m[0][0] * other[0][0] + m[0][1] * other[1][0];
		//matrix[0][1] = m[0][0] * other[0][1] + m[0][1] * other[1][1];
		//matrix[1][0] = m[1][0] * other[0][0] + m[1][1] * other[1][0];
		//matrix[1][1] = m[1][0] * other[0][1] + m[1][1] * other[1][1];

		float matrixSize = 2;
		for(unsigned int i = 0; i < matrixSize; i++)
		{
			for(unsigned int j = 0; j < matrixSize; j++)
			{
				matrix[i][j] = m[i][0] * other[0][j] + m[i][1] * other[1][j];
			}
		}
		return matrix;
	}

	vec2 & mat2::operator[](int index)
	{
		return m[index];
	}

	mat2 mat2::operator=(mat2 other)
	{
		unsigned int matrixSize = 2;
		for(unsigned int i = 0; i < matrixSize; i++)
		{
			for(unsigned int j = 0; j < matrixSize; j++)
			{
				m[i][j] = other[i][j];
			}
		}
		return *this;
	}

	bool mat2::operator==(mat2 other)
	{
		bool isTheSame = true;
		unsigned int matrixSize = 2;
		for(unsigned int i = 0; i < matrixSize; i++)
		{
			if(!isTheSame)
				break;
			for(unsigned int j = 0; j < matrixSize; j++)
			{
				if(m[i][j] != other[i][j])
				{
					isTheSame = false;
					break;
				}
			}
		}
		return isTheSame;
	}

	bool mat2::operator!=(mat2 other)
	{
		return !(*this == other);
	}

	mat2 operator*(float scalar, mat2 matrix)
	{
		return matrix * scalar;
	}
}