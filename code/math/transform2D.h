#pragma once

#include "mat3.h"

namespace LML
{
	class vec2;

	class transform2D
	{
	public:
		transform2D();
		~transform2D();

		void  translateBy(vec2 translation);
		void  rotateBy(float rotation);
		void  scaleBy(vec2 scale);

		void  setTranslation(vec2 translation);
		void  setRotation(float rotation);
		void  setScale(vec2 scale);

		vec2  getTranslation();
		float getRotation();
		vec2  getScale();

		vec2  getUpVector();
		vec2  getRightVector();

		mat3  getTransform();
		void  printToConsole();

	protected:
		mat3 translation;
		mat3 rotation;
		mat3 scale;
		mat3 finalTransform;

		bool dirty;
	};
}

#ifdef LML_TYPEDEFS
typedef LML::transform2D Transform2D;
#endif