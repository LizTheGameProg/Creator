
#ifndef __RENDERSPHERE_H__
#define __RENDERSPHERE_H__

#include <glm/glm.hpp>
#include <GL/glew.h>

//////////////////////////////////////////////////////////////////////////
//For arguments sake let's assume that we would like to have a vertex that 
//supports colours as well as UV's and vertex coordinates
// and also contains normals
//////////////////////////////////////////////////////////////////////////
struct VertexCN
{
	union
	{
		struct  
		{
			glm::vec4 position;
			glm::vec4 color;
			glm::vec4 normal;
			glm::vec2 uv;			
		};
		struct
		{
			float x, y, z, w;
			float r, g, b, a;
			float nx, ny, nz, nw;
			float u, v;			
		};
	};
};


class CRenderSphere
{
public:

	CRenderSphere	();
	CRenderSphere	(const glm::vec4& a_vCenter, int numRows, int numColumns, float radius, const glm::vec4& a_rvFillColour, const unsigned int a_uiTextureID = 0,
							 float longMin = 0.f, float longMax = 360, 
							 float latMin = -90, float latMax = 90);
	~CRenderSphere	();

	void Update		( float a_fDeltaTime );
	void Draw		( unsigned int uiShaderID );
	void SetTextureID( const unsigned int& uiTextureID );

protected:
	void GenerateGeometry();
private:

	unsigned int	m_VAO;
	unsigned int	m_VBO;
	unsigned int	m_IBO;
	
	unsigned int	m_TextureID;

	glm::mat4		m_m4PosRot;
	unsigned int	m_iNumRows;
	unsigned int	m_iNumCols;
	float			m_fRadius;

	glm::vec2		m_v2LongLatMin;
	glm::vec2		m_v2LongLatMax;
	glm::vec4		m_v4FillColor;

};

#endif //__RENDERSPHERE_H__
