#include "Shader.h"
#include "openGLBindings.h"

using namespace ANGINE;

unsigned int Shader::basicShaderID = 0;

const char * vsSource = "#version 410\n\nlayout(location=0) in vec4 Position;\nlayout(location=1) in vec2 TexCoord;\n\nout vec2 vTexCoord;\n\nuniform mat4 ProjectionView;\nuniform mat4 model;\n\nvoid main() {\nvTexCoord = TexCoord;\n	gl_Position = ProjectionView * model * Position;\n}";
const char * fsSource = "#version 410\n\nin vec2 vTexCoord;\n\nout vec4 FragColor;\n\nuniform sampler2D diffuse;\n\nvoid main() {\n	FragColor = texture(diffuse,vTexCoord);\n}";

Shader::Shader()
{

}

Shader::Shader(const char * vertexSource, const char * fragmentSource)
{
	//unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, (const char **)&vertexSource, 0);
	//glCompileShader(vertexShader);
	//
	//unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, (const char **)&fragmentSource, 0);
	//glCompileShader(fragmentShader);
	//
	//id = glCreateProgram();
	//glAttachShader(id, vertexShader);
	//glAttachShader(id, fragmentShader);
	//glLinkProgram(id);
	//
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	//glDeleteProgram(id);
}

unsigned int Shader::getBasicShaderID()
{
	if(basicShaderID != 0)
		return basicShaderID;
	
	
	//unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, (const char **)&vsSource, 0);
	//glCompileShader(vertexShader);
	//
	//unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, (const char **)&fsSource, 0);
	//glCompileShader(fragmentShader);
	//
	//basicShaderID = glCreateProgram();
	//glAttachShader(basicShaderID, vertexShader);
	//glAttachShader(basicShaderID, fragmentShader);
	//glLinkProgram(basicShaderID);
	//
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);

	return basicShaderID;
}