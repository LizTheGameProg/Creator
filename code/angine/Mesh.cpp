#include "Mesh.h"
#include "openGLBindings.h"

Mesh::Mesh()
{
	
}

Mesh::~Mesh()
{

}
//
//void Mesh::Load(const char * a_filePathName, Mesh::FileType a_type)
//{
//
//}
//
//void Mesh::init(const unsigned int a_indexData[])
//{
//	// Generate objects
//	glGenVertexArrays(1, &vao);
//	glGenBuffers(1, &vbo);
//	glGenBuffers(1, &ibo);
//
//	// Bind objects
//	glBindVertexArray(vao);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
//
//	// Bund data
//	//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, vertexData, GL_STATIC_DRAW);
//	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indexData, GL_STATIC_DRAW);
//	
//	// Enable Attributes
//	//glEnableVertexAttribArray(0);
//	//glEnableVertexAttribArray(1);
//
//	// Set Attribute data size
//	//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
//	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 6, ((char *) 0) + 16);
//
//	// Reset Bindings
//	glBindVertexArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//}