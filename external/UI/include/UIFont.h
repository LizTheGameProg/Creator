#pragma once
#include <freetype-gl.h>
#include <vertex-buffer.h>
#include <glm\glm.hpp>

class UIFont
{
public:
	UIFont(	const char * a_filePath, 
			wchar_t * a_glyphs, 
			wchar_t * a_text, 
			glm::vec2 * a_pen,
			glm::vec4 * a_colour,
			int a_fontSize,
			unsigned a_shaderID);
	~UIFont(void);
	void update(float a_deltaTime);
	void draw(glm::mat4 a_projection);
	void drawString(wchar_t * text, glm::vec2 pos, glm::vec4 a_colour = glm::vec4(0,0,0,1));

	glm::vec2	getPosition() {return m_position;}
	void		setPosition(glm::vec2 a_position) {m_position = a_position;}
	void		setSize(glm::vec2 a_size) {m_size = a_size;}

protected:
	typedef struct 
	{
	    float x, y, z;    // position
	    float s, t;       // texture
	    float r, g, b, a; // color
	} vertex_t;
	
	void addText(	vertex_buffer_t * a_buffer, 
					texture_font_t * a_font,
					wchar_t * a_text, 
					glm::vec4 * a_color, 
					glm::vec2 * a_pen );

	texture_atlas_t * m_atlas;
	vertex_buffer_t * m_buffer;
	texture_font_t  * m_font;
	unsigned int m_shaderID;
	glm::mat3 m_transform;
	glm::vec2 m_position;
	glm::vec2 m_size;
};

