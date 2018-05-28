#pragma once

class OpenGLInfo
{
public:
	OpenGLInfo();
	~OpenGLInfo();

	void generateOpenGLInfo();
	void deleteOpenGLInfo();


	unsigned int VAO;
	unsigned int VBO;
	unsigned int IBO;
};