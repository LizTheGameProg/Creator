#include "ShaderProgram.h"
#include "Utilities.h"
#include <iostream>
#include <glm/ext.hpp>

ShaderProgram::ShaderProgram(void)
{
	
}

ShaderProgram::~ShaderProgram(void)
{
	glDeleteProgram(m_ID);
}

void ShaderProgram::MakeProgram(std::map<ShaderType, const char *> a_shaderMap, const char * a_inputs[], unsigned int a_inputSize, const char * a_outputs[], unsigned int a_outputSize)
{
	//--------------------------------
	// Create 5 unsigned ints to pass through to the Utility::createProgram function
	//	: They are assigned to 0 so that if there isn't a shader of that type in the map they can be passed
	//	passed through to the createProgram as 0
	//--------------------------------
	unsigned int shaderIDs[5];
	shaderIDs[0] = 0;
	shaderIDs[1] = 0;
	shaderIDs[2] = 0;
	shaderIDs[3] = 0;
	shaderIDs[4] = 0;

	//--------------------------------
	// Foreach key pair value in the map create a shader based on the ShaderType 
	//	: if there isn't a shader of that type in the map then it is left at 0
	//--------------------------------
	for(auto kpv : a_shaderMap)
	{
		switch (kpv.first)
		{
		case VERT:
			{
				shaderIDs[0] = Utility::loadShader(kpv.second, kpv.first);
			}
			break;
		case TESS_CONT:
			{
				shaderIDs[1] = Utility::loadShader(kpv.second, kpv.first);
			}
			break;
		case TESS_EVAL:
			{
				shaderIDs[2] = Utility::loadShader(kpv.second, kpv.first);
			}
			break;
		case GEOM:
			{
				shaderIDs[3] = Utility::loadShader(kpv.second, kpv.first);
			}
			break;
		case FRAG:
			{
				shaderIDs[4] = Utility::loadShader(kpv.second, kpv.first);
			}
			break;
		default:
			break;
		}
	}

	// Create a program based on the shaders just created
	m_ID = Utility::createProgram(shaderIDs[0], shaderIDs[1], shaderIDs[2], shaderIDs[3], shaderIDs[4], a_inputSize, a_inputs, a_outputSize, a_outputs);

	// Delete the shaders that were just created as we don't need them anymore
	for(unsigned int i = 0; i < 5; i++)
	{
		glDeleteShader(i);
	}
}

void ShaderProgram::UseProgram()
{
	glUseProgram(m_ID);

	//GLint iUniform;
	//GLint fUniform;
	//GLint v2Uniform;
	//GLint v3Uniform;
	//GLint v4Uniform;
	//GLint m3Uniform;
	//GLint m4Uniform;
	//GLint tex0Uniform;
	//GLint tex1Uniform;
	//GLint tex2Uniform;
	//GLint tex3Uniform;
	//GLint tex4Uniform;
	//GLint tex5Uniform;
	//GLint tex6Uniform;
	//GLint tex7Uniform;
	//GLint boolUniform;

	//for(auto kvp : m_uInfo)
	//{
	//	switch (kvp.second.uType)
	//	{
	//	case INT:
	//		{
	//			iUniform = glGetUniformLocation(m_ID, kvp.first);
	//			GLint data = *(GLint *)kvp.second.uData;
	//			glUniform1i(iUniform, data);
	//		}
	//		break;
	//	case FLOAT:
	//		{
	//			fUniform = glGetUniformLocation(m_ID, kvp.first);
	//			glUniform1f(fUniform, *(GLfloat *)kvp.second.uData);
	//		}
	//		break;
	//	case VEC2:
	//		{
	//			v2Uniform = glGetUniformLocation(m_ID, kvp.first);
	//			glUniform2fv(v2Uniform, 1, glm::value_ptr(*(glm::vec2 *)kvp.second.uData));
	//		}
	//		break;
	//	case VEC3:
	//		{
	//			v3Uniform = glGetUniformLocation(m_ID, kvp.first);
	//			glUniform3fv(v3Uniform, kvp.second.uCount, glm::value_ptr(*(glm::vec3 *)kvp.second.uData));
	//		}
	//		break;
	//	case VEC4:
	//		{
	//			v4Uniform = glGetUniformLocation(m_ID, kvp.first);
	//			glUniform4fv(v4Uniform, kvp.second.uCount, glm::value_ptr(*(glm::vec4 *)kvp.second.uData));
	//		}
	//		break;
	//	case MAT3:
	//		{
	//			m3Uniform = glGetUniformLocation(m_ID, kvp.first);
	//			glUniformMatrix3fv(m3Uniform, kvp.second.uCount, false, glm::value_ptr(*(glm::mat3 *)(kvp.second.uData)));
	//		}
	//	case MAT4:
	//		{
	//			m4Uniform = glGetUniformLocation(m_ID, kvp.first);
	//			//glm::mat4 data = *(glm::mat4 *)kvp.second.uData;
	//			glUniformMatrix4fv(m4Uniform, kvp.second.uCount, false, glm::value_ptr(*(glm::mat4 *)(kvp.second.uData)));
	//		}
	//		break;
	//	case TEX0:
	//		{
	//			tex0Uniform = glGetUniformLocation(m_ID, kvp.first);
	//			glActiveTexture(GL_TEXTURE0);
	//			glBindTexture(GL_TEXTURE_2D, *(unsigned int*)kvp.second.uData);
	//			glUniform1i(tex0Uniform, 0);
	//		}
	//		break;
	//	case TEX1:
	//		{
	//			tex1Uniform = glGetUniformLocation(m_ID, kvp.first);
	//			glActiveTexture(GL_TEXTURE1);
	//			glBindTexture(GL_TEXTURE_2D, *(unsigned int*)kvp.second.uData);
	//			glUniform1i(tex1Uniform, 1);
	//		}
	//		break;
	//	case TEX2:
	//		{
	//			tex2Uniform = glGetUniformLocation(m_ID, kvp.first);
	//			glActiveTexture(GL_TEXTURE2);
	//			glBindTexture(GL_TEXTURE_2D, *(unsigned int*)kvp.second.uData);
	//			glUniform1i(tex2Uniform, 2);
	//		}
	//		break;
	//	case TEX3:
	//		{
	//			tex3Uniform = glGetUniformLocation(m_ID, kvp.first);
	//			glActiveTexture(GL_TEXTURE3);
	//			glBindTexture(GL_TEXTURE_2D, *(unsigned int*)kvp.second.uData);
	//			glUniform1i(tex3Uniform, 3);
	//		}
	//		break;
	//	case TEX4:
	//		{
	//			tex4Uniform = glGetUniformLocation(m_ID, kvp.first);
	//			glActiveTexture(GL_TEXTURE4);
	//			glBindTexture(GL_TEXTURE_2D, *(unsigned int*)kvp.second.uData);
	//			glUniform1i(tex4Uniform, 4);
	//		}
	//		break;
	//	case TEX5:
	//		{
	//			tex5Uniform = glGetUniformLocation(m_ID, kvp.first);
	//			glActiveTexture(GL_TEXTURE5);
	//			glBindTexture(GL_TEXTURE_2D, *(unsigned int*)kvp.second.uData);
	//			glUniform1i(tex5Uniform, 5);
	//		}
	//		break;
	//	case TEX6:
	//		{
	//			tex6Uniform = glGetUniformLocation(m_ID, kvp.first);
	//			glActiveTexture(GL_TEXTURE6);
	//			glBindTexture(GL_TEXTURE_2D, *(unsigned int*)kvp.second.uData);
	//			glUniform1i(tex6Uniform, 6);
	//		}
	//		break;
	//	case TEX7:
	//		{
	//			tex7Uniform = glGetUniformLocation(m_ID, kvp.first);
	//			glActiveTexture(GL_TEXTURE7);
	//			glBindTexture(GL_TEXTURE_2D, *(unsigned int*)kvp.second.uData);
	//			glUniform1i(tex7Uniform, 7);
	//		}
	//		break;
	//	case BOOL:
	//		{
	//			boolUniform = glGetUniformLocation(m_ID, kvp.first);
	//			if(*(bool *)kvp.second.uData)
	//			{
	//				glUniform1i(boolUniform, 0);
	//			}
	//			else
	//			{
	//				glUniform1i(boolUniform, 1);
	//			}
	//		}
	//		break;
	//	default:
	//		{
	//			std::cout << "Error: uInfo.uType was not set" << std::endl;
	//		}
	//		break;
	//	}
	//}
}