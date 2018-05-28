#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <map>
#include <GL/glew.h>
#include <vector>

enum ShaderType
{
	VERT		= GL_VERTEX_SHADER,
	TESS_CONT	= GL_TESS_CONTROL_SHADER,
	TESS_EVAL	= GL_TESS_EVALUATION_SHADER,
	GEOM		= GL_GEOMETRY_SHADER,
	FRAG		= GL_FRAGMENT_SHADER/*,
	COMP		= GL_COMPUTE_SHADER*/
};

enum UniformType
{
	INT = 0,
	FLOAT,
	VEC2,
	VEC3,
	VEC4,
	MAT3,
	MAT4,
	TEX0,
	TEX1,
	TEX2,
	TEX3,
	TEX4,
	TEX5,
	TEX6,
	TEX7,
	BOOL
};

struct UniformInfo
{
	UniformInfo(void){}
	UniformInfo(UniformType a_Type, void * a_Data, GLsizei a_Count = 1) : 
					uType(a_Type), 
					uData(a_Data),
					uCount(a_Count){}
	~UniformInfo(void){}
	UniformType uType;
	void * uData;
	GLsizei uCount;
};

struct cmp_str
{
   bool operator()(char const *a, char const *b)
   {
      return std::strcmp(a, b) < 0;
   }
};

class ShaderProgram
{
public:
	ShaderProgram(void);
	~ShaderProgram(void);

	unsigned int GetProgramID(){ return m_ID; }
	//std::map<const char *, UniformInfo, cmp_str> m_uInfo;

	void MakeProgram(std::map<ShaderType, const char *> a_shaderMap,// Map that contains the path to the shader and the type of shader it is
						const char * a_inputs[],					// Array of Input variables
						unsigned int a_inputSize,					// Size of the Input Array
						const char * a_outputs[],					// Array of outPut variables : is usually only "outColour"
						unsigned int a_outputSize					// Size of the Output Array
						);
	void UseProgram();
private:
	unsigned int m_ID;
	
};

#endif