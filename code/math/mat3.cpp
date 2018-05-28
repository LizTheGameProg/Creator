#include "mat3.h"
#include "mat2.h"
#include "common.h"
#include <iostream>

namespace LML
{
	#pragma region Constructors/Destructor
	mat3::mat3()
	{
		// Set everything to 0
		m[0] = vec3();
		m[1] = vec3();
		m[2] = vec3();

		// Set up the identity matrix (diagonals to 1)
		m[0][0] = 1.f;
		m[1][1] = 1.f;
		m[2][2] = 1.f;
	}

	mat3::mat3(	float a_m00, float a_m01, float a_m02, 
				float a_m10, float a_m11, float a_m12, 
				float a_m20, float a_m21, float a_m22)
	{
		m[0][0] = a_m00;
		m[0][1] = a_m01;
		m[0][2] = a_m02;

		m[1][0] = a_m10;
		m[1][1] = a_m11;
		m[1][2] = a_m12;

		m[2][0] = a_m20;
		m[2][1] = a_m21;
		m[2][2] = a_m22;
	}

	mat3::~mat3()
	{

	}
#pragma endregion
	
	#pragma region Utility
	mat3 mat3::transposed()
	{
		mat3 transposedMatrix;
		unsigned int matrixSize = 3;
		for(unsigned int i = 0; i < matrixSize; i++)
		{
			for(unsigned int j = 0; j < matrixSize; j++)
			{
				transposedMatrix[j][i] = m[i][j];
			}
		}
		return transposedMatrix;
	}

	mat3 mat3::inverse()
	{
		return (1.f / determinant()) * *this;
	}

	float mat3::determinant()
	{
		mat2 a(m[1][1], m[1][2], m[2][1], m[2][2]);
		mat2 b(m[1][0], m[1][2], m[2][0], m[2][2]);
		mat2 c(m[1][0], m[1][1], m[2][0], m[2][1]);

		return	(m[0][0] * a.determinant())
			-	(m[0][1] * b.determinant())
			+	(m[0][2] * c.determinant());
	}

	void mat3::printToConsole()
	{
		printf("|%f %f %f|\n|%f %f %f|\n|%f %f %f|\n", 
			m[0][0], m[0][1], m[0][2], 
			m[1][0], m[1][1], m[1][2], 
			m[2][0], m[2][1], m[2][2]);
	}
#pragma endregion

	#pragma region Operators
	mat3 mat3::operator*(float scalar)
	{
		mat3 matrix;

		float matrixSize = 3;
		for(unsigned int i = 0; i < matrixSize; i++)
		{
			for(unsigned int j = 0; j < matrixSize; j++)
			{
				matrix[i][j] = m[i][j] * scalar;
			}
		}

		return matrix;
	}
	
	vec3 mat3::operator*(vec3 other)
	{
		vec3 vector;
		for(unsigned int i = 0; i < 3; i++)
		{
			vector[i] = m[i][0] * other.x + m[i][1] * other.y + m[i][2] * other.z;
		}
		return vector;
	}
	
	mat3 mat3::operator*(mat3 other)
	{
		mat3 matrix;
		//
		//float matrixSize = 3;
		//for(unsigned int i = 0; i < matrixSize; i++)
		//{
		//	for(unsigned int j = 0; j < matrixSize; j++)
		//	{
		//		//vec3 v1(m[i][0], m[i][1], m[i][2]);
		//		vec3 v2(other[0][j], other[1][j], other[2][j]);
		//		matrix[i][j] = m[i].dot(v2);
		//		//vec3 vecColumn(m[0][j], m[1][j], m[2][j]);
		//		//matrix[i][j] = other[i].dot(vecColumn);
		//	}
		//}
		//
		
		float matrixSize = 3;
		for(unsigned int i = 0; i < matrixSize; i++)
		{
			for(unsigned int j = 0; j < matrixSize; j++)
			{
				matrix[i][j] = (m[i][0] * other[0][j]) + (m[i][1] * other[1][j]) + (m[i][2] * other[2][j]);
			}
		}
		
		/*
		A
		|00 01 02|
		|10 11 12|
		|20 21 22|

		B
		|00 01 02|
		|10 11 12|
		|20 21 22|

		C = A * B

		C.00 = A.00 * B.00 + A.01 * B.10 + A.02 * B.20
		C.01 = A.00 * B.01 + A.01 * B.11 + A.02 * B.21
		C.02 = A.00 * B.02 + A.01 * B.12 + A.02 * B.22

		C.10 = A.10 * B.00 + A.11 * B.10 + A.12 * B.20
		C.11 = A.10 * B.01 + A.11 * B.11 + A.12 * B.21
		C.12 = A.10 * B.02 + A.11 * B.12 + A.12 * B.22
		
		C.20 = A.20 * B.00 + A.21 * B.10 + A.22 * B.20
		C.21 = A.20 * B.01 + A.21 * B.11 + A.22 * B.21
		C.22 = A.20 * B.02 + A.21 * B.12 + A.22 * B.22
		*/

		return matrix;
	}

	mat3 mat3::operator=(mat3 other)
	{
		for(unsigned int i = 0; i < 3; i++)
		{
			for(unsigned int j = 0; j < 3; j++)
			{
				m[i][j] = other[i][j];
			}
		}
		return *this;
	}

	bool mat3::operator==(mat3 other)
	{
		bool isTheSame = true;
		unsigned int matrixSize = 3;
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

	bool mat3::operator!=(mat3 other)
	{
		return !(*this == other);
	}

	vec3 & mat3::operator[](int index)
	{
		return m[index];
	}

	mat3 operator*(float scalar, mat3 matrix)
	{
		return matrix * scalar;
	}
#pragma endregion
}