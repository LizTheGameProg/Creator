#include <GL/glew.h>
#include <glfw/glfw3.h>
#include <stdio.h>
#include <glm/ext.hpp>

#include "Utilities.h"

double Utility::sm_prevTime = 0;
float Utility::sm_deltaTime = 0;
float Utility::sm_totalTime = 0;

void Utility::resetTimer()
{
	sm_prevTime = glfwGetTime();
	sm_totalTime = 0;
	sm_deltaTime = 0;
}

float Utility::tickTimer()
{
	double currentTime = glfwGetTime();
	sm_deltaTime = (float)(currentTime - sm_prevTime);
	sm_totalTime += sm_deltaTime;
	sm_prevTime = currentTime;
	return sm_deltaTime;
}

// builds a simple 2 triangle quad with a position, colour and texture coordinates
void Utility::build3DPlane(float a_size, unsigned int& a_vao, unsigned int& a_vbo, unsigned int& a_ibo, const glm::vec4& a_colour /* = glm::vec4(1,1,1,1) */ )
{
	float halfSize = a_size * 0.5f;

	// create mesh
	BasicVertex vertices[4];
	vertices[0].position = glm::vec4(-halfSize,0,-halfSize,1);
	vertices[0].colour = a_colour;
	vertices[0].texCoord = glm::vec2(0,0);
	vertices[1].position = glm::vec4(halfSize,0,-halfSize,1);
	vertices[1].colour = a_colour;
	vertices[1].texCoord = glm::vec2(1,0);
	vertices[2].position = glm::vec4(halfSize,0,halfSize,1);
	vertices[2].colour = a_colour;
	vertices[2].texCoord = glm::vec2(1,1);
	vertices[3].position = glm::vec4(-halfSize,0,halfSize,1);
	vertices[3].colour = a_colour;
	vertices[3].texCoord = glm::vec2(0,1);

	unsigned int indices[6] = {
		3,1,0,
		3,2,1 
	};

	// create and bind buffers to a vertex array object
	glGenBuffers(1, &a_vbo);
	glGenBuffers(1, &a_ibo);
	glGenVertexArrays(1, &a_vao);

	glBindVertexArray(a_vao);
	glBindBuffer(GL_ARRAY_BUFFER, a_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, a_ibo);

	glBufferData(GL_ARRAY_BUFFER, 4* sizeof(BasicVertex), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(BasicVertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(BasicVertex), ((char*)0) + 16);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(BasicVertex), ((char*)0) + 32);

	// unbind vertex array
	glBindVertexArray(0);
}

// create a shader from an array of strings
unsigned int Utility::createShader(unsigned int a_stringCount, const char** a_strings, unsigned int a_type)
{
	int success = GL_FALSE;

	unsigned int handle = glCreateShader(a_type);

	glShaderSource(handle, a_stringCount, a_strings, 0);
	glCompileShader(handle);
		
	glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		int infoLogLength = 0;		
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];

		glGetShaderInfoLog(handle, infoLogLength, 0, infoLog);
		printf("Error: Failed to compile shader!\n");
		printf("%s",infoLog);
		printf("\n");
		delete[] infoLog;
		return 0;
	}

	return handle;
}

// loads a shader from a file and creates it for the specified stage
unsigned int Utility::loadShader(const char* a_filename, unsigned int a_type)
{
	int success = GL_FALSE;

	unsigned char* source = fileToBuffer(a_filename);
	unsigned int handle = glCreateShader(a_type);

	glShaderSource(handle, 1, (const char**)&source, 0);
	glCompileShader(handle);
	
	delete[] source;

	glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		int infoLogLength = 0;		
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];

		glGetShaderInfoLog(handle, infoLogLength, 0, infoLog);
		printf("Error: Failed to compile shader!\n");
		printf("%s",infoLog);
		printf("\n");
		delete[] infoLog;
		return 0;
	}

	return handle;
}

// creates a shader program, links the specified shader stages to it, and binds the specified input/output attributes
unsigned int Utility::createProgram(unsigned int a_vertexShader, unsigned int a_controlShader, unsigned int a_evaluationShader, unsigned int a_geometryShader, unsigned int a_fragmentShader,
								  unsigned int a_inputAttributeCount /* = 0 */, const char** a_inputAttributes /* = nullptr */,
								  unsigned int a_outputAttributeCount /* = 0 */, const char** a_outputAttributes /* = nullptr */)
{
	int success = GL_FALSE;

	// create a shader program and attach the shaders to it
	unsigned int handle = glCreateProgram();
	glAttachShader(handle, a_vertexShader);
	glAttachShader(handle, a_controlShader);
	glAttachShader(handle, a_evaluationShader);
	glAttachShader(handle, a_geometryShader);
	glAttachShader(handle, a_fragmentShader);

	// specify vertex input attributes
	for ( unsigned int i = 0 ; i < a_inputAttributeCount ; ++i )
		glBindAttribLocation(handle, i, a_inputAttributes[i]);

	// specify fragment shader outputs
	for ( unsigned int i = 0 ; i < a_outputAttributeCount ; ++i )
		glBindFragDataLocation(handle, i, a_outputAttributes[i]);

	// link the program together and log errors
	glLinkProgram(handle);

	glGetProgramiv(handle, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		int infoLogLength = 0;		
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];

		glGetShaderInfoLog(handle, infoLogLength, 0, infoLog);
		printf("Error: Failed to link shader program!\n");
		printf("%s",infoLog);
		printf("\n");
		delete[] infoLog;
		return 0;
	}

	return handle;
}

unsigned char* Utility::fileToBuffer(const char* a_filename)
{
	// open file for text reading
	FILE* pFile = fopen(a_filename,"rb");
	if (pFile == nullptr)
	{
		printf("Error: Unable to open file '%s' for reading!\n",a_filename);
		return nullptr;
	}

	// get number of bytes in file
	fseek(pFile, 0, SEEK_END);
	unsigned int uiLength = (unsigned int)ftell(pFile);
	fseek(pFile, 0, SEEK_SET);

	// allocate buffer and read file contents
	unsigned char* acBuffer = new unsigned char[uiLength + 1];
	memset(acBuffer,0,uiLength + 1);
	fread(acBuffer, sizeof(unsigned char), uiLength, pFile);

	fclose(pFile);
	return acBuffer;
}

void Utility::freeMovement(glm::mat4& a_transform, float a_deltaTime, float a_speed, const glm::vec3& a_up /* = glm::vec3(0,1,0) */)
{
	GLFWwindow* window = glfwGetCurrentContext();

	float frameSpeed = glfwGetKey(window,GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? a_deltaTime * a_speed * 2 : a_deltaTime * a_speed;	

	// translate
	if (glfwGetKey(window,'W') == GLFW_PRESS)
		a_transform[3] -= a_transform[2] * frameSpeed;
	if (glfwGetKey(window,'S') == GLFW_PRESS)
		a_transform[3] += a_transform[2] * frameSpeed;
	if (glfwGetKey(window,'D') == GLFW_PRESS)
		a_transform[3] += a_transform[0] * frameSpeed;
	if (glfwGetKey(window,'A') == GLFW_PRESS)
		a_transform[3] -= a_transform[0] * frameSpeed;
	if (glfwGetKey(window,'Q') == GLFW_PRESS)
		a_transform[3] += a_transform[1] * frameSpeed;
	if (glfwGetKey(window,'E') == GLFW_PRESS)
		a_transform[3] -= a_transform[1] * frameSpeed;
	
	// check for rotation
	static bool sbMouseButtonDown = false;
	if (glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
	{
		static double siPrevMouseX = 0;
		static double siPrevMouseY = 0;

		if (sbMouseButtonDown == false)
		{
			sbMouseButtonDown = true;
			glfwGetCursorPos(window,&siPrevMouseX,&siPrevMouseY);
		}

		double mouseX = 0, mouseY = 0;
		glfwGetCursorPos(window,&mouseX,&mouseY);

		double iDeltaX = mouseX - siPrevMouseX;
		double iDeltaY = mouseY - siPrevMouseY;

		siPrevMouseX = mouseX;
		siPrevMouseY = mouseY;

		glm::mat4 mMat;
		
		// pitch
		if (iDeltaY != 0)
		{
			mMat = glm::axisAngleMatrix( a_transform[0].xyz(), (float)-iDeltaY / 150.0f );
			a_transform[0] = mMat * a_transform[0];
			a_transform[1] = mMat * a_transform[1];
			a_transform[2] = mMat * a_transform[2];
		}

		// yaw
		if (iDeltaX != 0)
		{
			mMat = glm::axisAngleMatrix( a_up, (float)-iDeltaX / 150.0f );
			a_transform[0] = mMat * a_transform[0];
			a_transform[1] = mMat * a_transform[1];
			a_transform[2] = mMat * a_transform[2];
		}
	}
	else
	{
		sbMouseButtonDown = false;
	}
}