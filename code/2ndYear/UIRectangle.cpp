#include "UIRectangle.h"
#include <GL/glew.h>
#include <glm/ext.hpp>

UIRectangle::UIRectangle(void)
{

}

UIRectangle::UIRectangle(unsigned int a_shader,
						 const vec2 & a_dimensions /*= vec2(1,1)*/,
						 const vec4 & a_colour /*= vec4(1,1,1,1)*/) :
						m_shader(a_shader),
						m_vao(0), m_vbo(0),
						m_dimensions(a_dimensions),
						m_colour(a_colour),
						m_texture(0)
{
	m_textureCoords[0] = vec2(0,1);
	m_textureCoords[1] = vec2(0,0);
	m_textureCoords[2] = vec2(1,1);
	m_textureCoords[3] = vec2(1,0);

	glm::vec3 vertices[4] = 
	{
		glm::vec3(-0.5f,  0.5f, 1),
		glm::vec3(-0.5f, -0.5f, 1),
		glm::vec3( 0.5f,  0.5f, 1),
		glm::vec3( 0.5f, -0.5f, 1)
	};

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(glm::vec3), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glBindVertexArray(0);
}
							

UIRectangle::~UIRectangle(void)
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
}

void UIRectangle::draw(const glm::mat4 & a_projection)
{
	int program = -1;
	glGetIntegerv(GL_CURRENT_PROGRAM, &program);

	if(program != m_shader)
		glUseProgram(m_shader);

	int location = glGetUniformLocation(m_shader, "projection");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(a_projection));

	mat3 transform = getTransform();
	location = glGetUniformLocation(m_shader, "transform");
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(transform));

	location = glGetUniformLocation(m_shader, "dimensions");
	glUniform2f(location, m_dimensions.x, m_dimensions.y);

	location = glGetUniformLocation(m_shader, "colour");
	glUniform4fv(location, 1, glm::value_ptr(m_colour));

	location = glGetUniformLocation(m_shader, "textureCoords");
	glUniform2fv(location, 4, (float *)m_textureCoords);
	
	location = glGetUniformLocation(m_shader, "diffuseMap");
	glUniform1i(location, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	UIElement::draw(a_projection);

	if(program != m_shader)
		glUseProgram(program);
}
