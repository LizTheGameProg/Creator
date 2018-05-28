#include "mat4.h"
#include "mat3.h"
#include <iostream>

namespace LML
{
	#pragma region Constructors/Destructor
	mat4::mat4()
	{
		m[0] = vec4();
		m[1] = vec4();
		m[2] = vec4();
		m[3] = vec4();

		m[0][0] = 1.f;
		m[1][1] = 1.f;
		m[2][2] = 1.f;
		m[3][3] = 1.f;
	}

	mat4::~mat4()
	{
	
	}
#pragma endregion

	#pragma region Utility
	mat4 mat4::transposed()
	{
		mat4 transposedMatrix;
		unsigned int matrixSize = 4;
		for(unsigned int i = 0; i < matrixSize; i++)
		{
			for(unsigned int j = 0; j < matrixSize; j++)
			{
				transposedMatrix[j][i] = m[i][j];
			}
		}
		return transposedMatrix;
	}

	mat4 mat4::inverse()
	{
		return (1.f / determinant()) * *this;
	}

	float mat4::determinant()
	{
		mat3 a(	m[1][1], m[1][2], m[1][3],
				m[2][1], m[2][2], m[2][3],
				m[3][1], m[3][2], m[3][3]);
		mat3 b(	m[1][0], m[1][2], m[1][3],
				m[2][0], m[2][2], m[2][3],
				m[3][0], m[3][2], m[3][3]);
		mat3 c(	m[1][0], m[1][1], m[1][3],
				m[2][0], m[2][1], m[2][3],
				m[3][0], m[3][1], m[3][3]);
		mat3 d(	m[1][0], m[1][1], m[1][2],
				m[2][0], m[2][1], m[2][2],
				m[3][0], m[3][1], m[3][2]);

		return	(m[0][0] * a.determinant()) - 
				(m[0][1] * b.determinant()) + 
				(m[0][2] * c.determinant()) - 
				(m[0][3] * d.determinant());
	}

	void mat4::printToConsole()
	{
		printf("|%f %f %f %f|\n|%f %f %f %f|\n|%f %f %f %f|\n|%f %f %f %f|\n", 
			m[0][0], m[0][1], m[0][2], m[0][3],
			m[1][0], m[1][1], m[1][2], m[1][3],
			m[2][0], m[2][1], m[2][2], m[2][3],
			m[3][0], m[3][1], m[3][2], m[3][3]);
	}
#pragma endregion

	#pragma region Operators
	mat4 mat4::operator*(float scalar)
	{
		mat4 matrix;

		float matrixSize = 4;
		for(unsigned int i = 0; i < matrixSize; i++)
		{
			for(unsigned int j = 0; j < matrixSize; j++)
			{
				matrix[i][j] = m[i][j] * scalar;
			}
		}

		return matrix;
	}
	
	vec4 mat4::operator*(vec4 other)
	{
		vec4 vector;
		for(unsigned int i = 0; i < 4; i++)
		{
			vector[i] = m[i][0] * other.x + m[i][1] * other.y + m[i][2] * other.z + m[i][3] * other.w;
		}
		return vector;
	}
	
	mat4 mat4::operator*(mat4 other)
	{
		mat4 matrix;
		
		float matrixSize = 4;
		for(unsigned int i = 0; i < matrixSize; i++)
		{
			for(unsigned int j = 0; j < matrixSize; j++)
			{
				matrix[i][j] = (m[i][0] * other[0][j]) + (m[i][1] * other[1][j]) + (m[i][2] * other[2][j]) + (m[i][3] * other[3][j]);
			}
		}
		
		return matrix;
	}

	mat4 mat4::operator=(mat4 other)
	{
		for(unsigned int i = 0; i < 4; i++)
		{
			for(unsigned int j = 0; j < 4; j++)
			{
				m[i][j] = other[i][j];
			}
		}
		return *this;
	}

	bool mat4::operator==(mat4 other)
	{
		bool isTheSame = true;
		unsigned int matrixSize = 4;
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

	bool mat4::operator!=(mat4 other)
	{
		return !(*this == other);
	}

	vec4 & mat4::operator[](int index)
	{
		return m[index];
	}

	mat4 operator*(float scalar, mat4 matrix)
	{
		return matrix * scalar;
	}
#pragma endregion
}