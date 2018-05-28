#include "transform2D.h"
#include "vec2.h"
#include "common.h"
#include <iostream>

namespace LML
{
	transform2D::transform2D()
	{
		translation = LML::mat3();
		rotation = LML::mat3();
		scale = LML::mat3();
		dirty = true;
	}

	transform2D::~transform2D()
	{

	}

	void transform2D::translateBy(vec2 a_translation)
	{
		mat3 l_translation;
		l_translation[2][0] = a_translation.x;
		l_translation[2][1] = a_translation.y;
		translation = translation * l_translation;

		dirty = true;
	}

	void transform2D::rotateBy(float a_rotation)
	{
		mat3 l_rotation;
		l_rotation[0][0] = cos(a_rotation);
		l_rotation[0][1] = sin(a_rotation);
		l_rotation[1][0] = -sin(a_rotation);
		l_rotation[1][1] = cos(a_rotation);
		rotation = rotation * l_rotation;

		dirty = true;
	}

	void transform2D::scaleBy(vec2 a_scale)
	{
		mat3 l_scale;
		l_scale[0][0] = a_scale.x;
		l_scale[1][1] = a_scale.y;
		scale = scale * l_scale;

		dirty = true;
	}

	void transform2D::setTranslation(vec2 a_translation)
	{
		translation[2][0] = a_translation.x;
		translation[2][1] = a_translation.y;

		dirty = true;
	}

	void transform2D::setRotation(float a_rotation)
	{
		rotation[0][0] = cos(a_rotation);
		rotation[0][1] = sin(a_rotation);
		rotation[1][0] = -sin(a_rotation);
		rotation[1][1] = cos(a_rotation);

		dirty = true;
	}

	void transform2D::setScale(vec2 a_scale)
	{
		scale[0][0] = a_scale.x;
		scale[1][1] = a_scale.y;

		dirty = true;
	}

	vec2 transform2D::getTranslation()
	{
		return vec2(translation[2][0], translation[2][1]);
	}

	float transform2D::getRotation()
	{
		return atan2(-rotation[1][0], rotation[0][0]);
	}

	vec2 transform2D::getScale()
	{
		vec2 l_scale;
		l_scale.x = scale[0][0];
		l_scale.y = scale[1][1];
		return l_scale;
	}

	vec2 transform2D::getUpVector()
	{
		mat3 l_transform = getTransform();
		vec2 l_up(l_transform[1].x, l_transform[1].y);
		l_up.normalise();
		return l_up;
	}

	vec2 transform2D::getRightVector()
	{
		mat3 l_transform = getTransform();
		vec2 l_right(l_transform[0].x, l_transform[0].y);
		l_right.normalise();
		return l_right;
	}

	mat3 transform2D::getTransform()
	{
		if(dirty)
		{
			dirty = false;
			finalTransform = scale * rotation * translation;
		}
		
		return finalTransform;
	}

	void transform2D::printToConsole()
	{
		vec2  l_position	= getTranslation();
		float l_rotation	= getRotation();
		vec2  l_scale		= getScale();
		printf("Position: %f, %f.\nRotation: %f.\nScale: %f, %f.\n", l_position.x, l_position.y, l_rotation, l_scale.x, l_scale.y);
	}
}