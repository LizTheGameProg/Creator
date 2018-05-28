#pragma once
#include "OpenGLInfo.h"

class Grid
{
public:
	Grid();
	~Grid();

private:
	unsigned int m_rows;
	unsigned int m_collumns;
	OpenGLInfo m_openGLInfo;
	
};

