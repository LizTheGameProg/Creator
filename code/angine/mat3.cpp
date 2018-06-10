#include "mat3.h"

namespace ANGINE
{
	mat3::mat3()
	{
		data[0] = vec3();
		data[0].x = 1.f;

		data[1] = vec3();
		data[1].y = 1.f;

		data[2] = vec3();
		data[2].z = 1.f;
	}

	mat3::mat3(vec3 & v0, vec3 & v1, vec3 & v2)
	{
		data[0] = v0;
		data[1] = v1;
		data[2] = v2;
	}

	mat3::mat3(mat3 & other)
	{
		data[0] = other.data[0];
		data[1] = other.data[1];
		data[2] = other.data[2];
	}

	mat3::~mat3()
	{
		data[0] = vec3();
		data[1] = vec3();
		data[2] = vec3();
	}

	mat3 mat3::operator+(mat3 & other)
	{
		mat3 value;
		value.data[0] = data[0] + data[0];
		value.data[1] = data[1] + data[1];
		value.data[2] = data[2] + data[2];
		return value;
	}

	mat3 mat3::operator-(mat3 & other)
	{
		mat3 value;
		value.data[0] = data[0] - data[0];
		value.data[1] = data[1] - data[1];
		value.data[2] = data[2] - data[2];
		return value;
	}

	vec3 mat3::operator*(vec3 & other)
	{
		vec3 result;

		result.x = data[0].dot(other);
		result.y = data[1].dot(other);
		result.z = data[2].dot(other);
		
		return result;
	}

	mat3 mat3::operator*(mat3 & other)
	{
		mat3 result;

		for(unsigned int i = 0; i < 3; i++)
		{
			for(unsigned int j = 0; j < 3; j++)
			{
				result[i][j] = data[i][0] * other[0][j] + data[i][1] * other[1][j] + data[i][2] * other[2][j];
			}
		}
		/*
		 m1   m2
		123	  123
		456 * 456
		789	  789
		*/
		/*
		result[0][0] = data[0][0] * other.data[0][0] + data[0][1] * other.data[1][0] + data[0][2] * other.data[2][0];
		result[0][1] = data[0][0] * other.data[0][1] + data[0][1] * other.data[1][1] + data[0][2] * other.data[2][1];
		result[0][2] = data[0][0] * other.data[0][2] + data[0][1] * other.data[1][2] + data[0][2] * other.data[2][2];

		result[0][0] = data[1][0] * other.data[0][0] + data[1][1] * other.data[1][0] + data[1][2] * other.data[2][0];
		result[0][1] = data[1][0] * other.data[0][1] + data[1][1] * other.data[1][1] + data[1][2] * other.data[2][1];
		result[0][2] = data[1][0] * other.data[0][2] + data[1][1] * other.data[1][2] + data[1][2] * other.data[2][2];

		result[0][0] = data[2][0] * other.data[0][0] + data[2][1] * other.data[1][0] + data[2][2] * other.data[2][0];
		result[0][1] = data[2][0] * other.data[0][1] + data[2][1] * other.data[1][1] + data[2][2] * other.data[2][1];
		result[0][2] = data[2][0] * other.data[0][2] + data[2][1] * other.data[1][2] + data[2][2] * other.data[2][2];
		*/
		return result;
	}

	vec3 & mat3::operator[](int index)
	{
		return data[index];
	}
}