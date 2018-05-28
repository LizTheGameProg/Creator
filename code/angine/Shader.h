#pragma once

class Shader
{
public:
	 Shader(const char * vertexSource, const char * fragmentSource);
	 ~Shader();
	
	 unsigned int getID() { return id; }

	 static unsigned int getBasicShaderID();
private:
	 Shader();

	unsigned int id;
	static unsigned int basicShaderID;
};