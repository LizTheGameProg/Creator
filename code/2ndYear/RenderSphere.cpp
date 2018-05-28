
#include "RenderSphere.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

CRenderSphere::CRenderSphere()
{
	//////////////////////////////////////////////////////////////////////////////
	//Assign Member Variables
	/////////////////////////////////////////////////////////////////////////////
	m_m4PosRot		= glm::mat4( 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 10.f, 0.f, 1.f );
	m_iNumRows		= 64;
	m_iNumCols		= 64;
	m_fRadius		= 12.f;
	
	m_v2LongLatMin	= glm::vec2( 0.f, -90.f );
	m_v2LongLatMax	= glm::vec2( 360.4, 90.f );
	
	m_v4FillColor	= glm::vec4( 1.f, 1.f, 1.f, 1.f );
	m_TextureID		= 0;

	GenerateGeometry();
	
}

CRenderSphere::CRenderSphere(const glm::vec4& a_vCenter, int numRows, int numColumns, float radius, const glm::vec4& a_rvFillColour, const unsigned int a_uiTextureID /*= 0*/,
							 float longMin /*= 0.f*/, float longMax /*= 360*/, 
							 float latMin /*= -90*/, float latMax /*= 90*/)
{
	//////////////////////////////////////////////////////////////////////////////
	//Assign Member Variables
	/////////////////////////////////////////////////////////////////////////////
	m_m4PosRot		= glm::mat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
	m_m4PosRot[3]	= a_vCenter;
	m_iNumRows		= numRows;
	m_iNumCols		= numColumns;
	m_fRadius		= radius;
	
	m_v2LongLatMin	= glm::vec2( 0.f, -90.f );
	m_v2LongLatMax	= glm::vec2( 360.f, 90.f );
	
	m_v4FillColor	= a_rvFillColour;
	m_TextureID		= a_uiTextureID;
	GenerateGeometry();
	
}

CRenderSphere::~CRenderSphere()
{
	glDeleteBuffers( 1, &m_VBO );
	glDeleteBuffers( 1, &m_IBO );
	glDeleteVertexArrays( 1, &m_VAO );
}

void CRenderSphere::GenerateGeometry()
{
	//////////////////////////////////////////////////////////////////////////////
	// Fill Vertex Array and Index Array to pass to GPU
	//////////////////////////////////////////////////////////////////////////////
	unsigned int iNumVerts	= (m_iNumRows+1) * (m_iNumCols+1);
	//Invert these first as the multiply is slightly quicker
	float inverseRadius		= 1.0f/m_fRadius;
	float invColumns		= 1.0f/float(m_iNumCols);
	float invRows			= 1.0f/float(m_iNumRows);
	
	float DEG2RAD = glm::pi<float>() / 180;
	//Lets put everything in radians first
	float latitiudinalRange = (m_v2LongLatMax.y - m_v2LongLatMin.y) * DEG2RAD;
	float longitudinalRange = (m_v2LongLatMax.x - m_v2LongLatMin.x) * DEG2RAD;
	//Create a vertex array to hold the data
	//VertexCN* vertexArray = new VertexCN[iNumVerts];
	// for each row of the mesh
	for (unsigned int row = 0; row <= m_iNumRows; ++row)
	{
		// y ordinates this may be a little confusing but here we are navigating around the xAxis in GL
		float ratioAroundXAxis		= float(row) * invRows;
		float v_textureCoordinate	= fabsf(ratioAroundXAxis);
		float radiansAboutXAxis		= ratioAroundXAxis * latitiudinalRange + (m_v2LongLatMin.y * DEG2RAD);
		
		float y						=  m_fRadius * sin(radiansAboutXAxis);
		float z						=  m_fRadius * cos(radiansAboutXAxis);
		
		for (unsigned  int col = 0; col <= m_iNumCols; ++col )
		{
			float ratioAroundYAxis		= float(col) * invColumns;
			float u_textureCoordinate	= fabsf(1.0f-ratioAroundYAxis);
			float theta					= ratioAroundYAxis * longitudinalRange + (m_v2LongLatMin.x * DEG2RAD);
			int index					= row * (m_iNumCols+1) + (col % (m_iNumCols+1));
			//vertexArray[index].position	= glm::vec4( -z * sinf(theta), y, -z * cosf(theta), 1.f );
			//vertexArray[index].normal	= vertexArray[index].position * inverseRadius;
			//vertexArray[index].normal.w = 0.f; //As we are a normal vector and not a Position
			//vertexArray[index].uv		= glm::vec2( u_textureCoordinate, v_textureCoordinate);
			//vertexArray[index].color	= m_v4FillColor;
		}
	}
	
	unsigned int indexCount		= iNumVerts * 6;
	unsigned int* uiIndexArray	= new unsigned int[indexCount];
	
	unsigned int index			= 0;
	for (unsigned int face = 0; face <= iNumVerts; ++face )
	{
		int iNextFace = face+1;
		if( iNextFace % (m_iNumCols+1) == 0 )
		{
			continue;
		}
		/////////////////////////////////////////////////////////////////////////
		//For Renedering of Sphere Triangle Geometry
		/////////////////////////////////////////////////////////////////////////
		uiIndexArray[index]		= iNextFace;
		uiIndexArray[index+2]	= face;
		uiIndexArray[index+1]	= iNextFace + m_iNumCols;

		uiIndexArray[index+3]	= iNextFace;
		uiIndexArray[index+5]	= iNextFace + m_iNumCols;
		uiIndexArray[index+4]	= iNextFace+1 + m_iNumCols;
		index+=6;
		/////////////////////////////////////////////////////////////////////////
		
	}
	//////////////////////////////////////////////////////////////////////////////
	// create VBOs For Triangle Geometry
	glGenBuffers( 1, &m_VBO );
	glGenBuffers( 1, &m_IBO );
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	//glBufferData(GL_ARRAY_BUFFER, iNumVerts * sizeof(VertexCN), vertexArray, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), uiIndexArray, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(VertexCN), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE , sizeof(VertexCN), ((char*)0) + 16);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_TRUE , sizeof(VertexCN), ((char*)0) + 32);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_TRUE , sizeof(VertexCN), ((char*)0) + 48);	
	
	glBindVertexArray(0);
	
	/////////////////////////////////////////////////////////////////////////
	delete[] uiIndexArray;
	//delete[] vertexArray;
	
}

void CRenderSphere::SetTextureID( const unsigned int& uiTextureID )
{
	m_TextureID = uiTextureID;
}

void CRenderSphere::Update( float a_fDeltaTime )
{
	static float sfTimer = glm::pi<float>();
	sfTimer += a_fDeltaTime;
	//m_m4PosRot.RotateY(sfTimer);
}

void CRenderSphere::Draw( unsigned int uiShaderID )
{
	GLuint ModelID = glGetUniformLocation(uiShaderID,"Model");
	glUniformMatrix4fv(ModelID, 1, false, glm::value_ptr(m_m4PosRot));

	glBindVertexArray(m_VAO);
	unsigned int indexCount = (m_iNumRows)*m_iNumCols*6;
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

}