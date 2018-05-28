#include "Tutorial2.h"
#include "Gizmos.h"
#include "Utilities.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#define DEFAULT_SCREENWIDTH 1280
#define DEFAULT_SCREENHEIGHT 720

using namespace AIE_2ND_YEAR;

Tutorial2::Tutorial2()
{

}

Tutorial2::~Tutorial2()
{

}

bool Tutorial2::onCreate(int a_argc, char* a_argv[]) 
{
	// initialise the Gizmos helper class
	Gizmos::create();

	// create a world-space matrix for a camera
	m_cameraMatrix = glm::inverse( glm::lookAt(glm::vec3(10,10,10),glm::vec3(0,0,0), glm::vec3(0,1,0)) );
	
	// create a perspective projection matrix with a 90 degree field-of-view and widescreen aspect ratio
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, DEFAULT_SCREENWIDTH/(float)DEFAULT_SCREENHEIGHT, 0.1f, 1000.0f);

	// set the clear colour and enable depth testing and backface culling
	glClearColor(0.25f,0.25f,0.25f,1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	m_rows = 10;
	m_cols = 10;

	m_time = 0.f;

	GenerateGrid(m_rows, m_cols);

	// create shaders
	const char* vsSource = "#version 150\n \
					in vec4 Position; \
					in vec4 Colour; \
					out vec4 vColour; \
					out float vtime; \
					out float vHeightScale; \
					out vec4 vPosition; \
					uniform mat4 ProjectionView; \
					uniform float time; \
					uniform float heightScale; \
					void main() { \
					vec4 P = Position; \
					P.y += sin( time + Position.x ) * heightScale; \
					P.y += cos( time + Position.z ) * heightScale; \
					vColour = Colour; \
					vtime = time; \
					vHeightScale = heightScale; \
					gl_Position = ProjectionView * P; \
					vPosition = P;}";
	
	const char* fsSource = "#version 150\n \
					in vec4 vColour; \
					in vec4 vPosition; \
					uniform float time; \
					uniform float heightScale; \
					out vec4 FragColor; \
					void main()	{ vec4 C = vColour; \
					C.r += sin( time * vColour.r) * heightScale; \
					C.g += cos( time * vColour.g) * heightScale; \
					C.b += tan( time * vColour.b) * heightScale; \
					FragColor = C;}";
		
	int success = GL_FALSE;
		
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	glShaderSource(vertexShader, 1, (const char**)&vsSource, 0);
	glCompileShader(vertexShader);
		
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];
			
		glGetShaderInfoLog(vertexShader, infoLogLength, 0, infoLog);
		printf("Error: Failed to compile vertex shader!\n");
		printf("%s",infoLog);
		printf("\n");
		delete[] infoLog;
	}
	
	glShaderSource(fragmentShader, 1, (const char**)&fsSource, 0);
	glCompileShader(fragmentShader);
		
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];
			
		glGetShaderInfoLog(fragmentShader, infoLogLength, 0, infoLog);
		printf("Error: Failed to compile fragment shader!\n");
		printf("%s",infoLog);
		printf("\n");
		delete[] infoLog;
	}
		
	m_programID = glCreateProgram();
	glAttachShader(m_programID, vertexShader);
	glAttachShader(m_programID, fragmentShader);
	glBindAttribLocation(m_programID, 0, "Position");
	glBindAttribLocation(m_programID, 1, "Colour");
	glLinkProgram(m_programID);
		
	glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetShaderiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];
			
		glGetShaderInfoLog(m_programID, infoLogLength, 0, infoLog);
		printf("Error: Failed to link shader program!\n");
		printf("%s",infoLog);
		printf("\n");
		delete[] infoLog;
	}
	
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	return true;
}

void Tutorial2::onUpdate(float a_deltaTime) 
{
	// update our camera matrix using the keyboard/mouse
	Utility::freeMovement( m_cameraMatrix, a_deltaTime, 10 );

	// clear all gizmos from last frame
	Gizmos::clear();
	
	m_time += a_deltaTime * 5;

	//// add an identity matrix gizmo
	//Gizmos::addTransform( glm::mat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1) );
	//
	//// add a 20x20 grid on the XZ-plane
	//for ( int i = 0 ; i < 21 ; ++i )
	//{
	//	Gizmos::addLine( glm::vec3(-10 + i, 0, 10), glm::vec3(-10 + i, 0, -10), 
	//					 i == 10 ? glm::vec4(1,1,1,1) : glm::vec4(0,0,0,1) );
	//	
	//	Gizmos::addLine( glm::vec3(10, 0, -10 + i), glm::vec3(-10, 0, -10 + i), 
	//					 i == 10 ? glm::vec4(1,1,1,1) : glm::vec4(0,0,0,1) );
	//}

	// quit our application when escape is pressed
	if (glfwGetKey(m_window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		quit();
}

void Tutorial2::onDraw() 
{
	// clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// get the view matrix from the world-space camera matrix
	glm::mat4 viewMatrix = glm::inverse( m_cameraMatrix );
	
	// draw the gizmos from this frame
	Gizmos::draw(viewMatrix, m_projectionMatrix);

	//glDisable(GL_CULL_FACE);
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	glUseProgram(m_programID);
	unsigned int projectionViewUniform = glGetUniformLocation(m_programID,"ProjectionView");
	glUniformMatrix4fv(projectionViewUniform, 1, false, glm::value_ptr(m_projectionMatrix * viewMatrix));
	
	unsigned int timeUniform = glGetUniformLocation(m_programID, "time");
	glUniform1f(timeUniform, m_time);

	const float fheightScale = 0.3f;
	unsigned int heightScaleUniform = glGetUniformLocation(m_programID,"heightScale");
	glUniform1f(heightScaleUniform, fheightScale);

	glBindVertexArray(m_VAO);
	unsigned int indexCount = (m_rows - 1) * (m_cols - 1) * 6;
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	
}

void Tutorial2::onDestroy()
{
	// clean up anything we created
	Gizmos::destroy();
}

// main that controls the creation/destruction of an application
int main(int argc, char* argv[])
{
	// explicitly control the creation of our application
	AIE_2ND_YEAR::Application* app = new Tutorial2();
	
	if (app->create("AIE - Tutorial2",DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT,argc,argv) == true)
		app->run();
		
	// explicitly control the destruction of our application
	delete app;

	return 0;
}

// function to create a grid
void Tutorial2::GenerateGrid( unsigned int rows, unsigned int cols )
{
	V_4v_4c* aoVertices = new V_4v_4c[ rows * cols ];

	for ( unsigned int r = 0 ; r < rows ; ++r )
	{
		for ( unsigned int c = 0 ; c < cols ; ++c )
		{
			aoVertices[ r * cols + c ].position = glm::vec4((float)c, 0, (float)r, 1);
                        //Create some arbitrary colour based off something 
                        //that might not be related to tiling a texture
                        glm::vec3 v3colour = glm::vec3( (sinf( (c / (float)(cols - 1)) *  ( r / (float)(rows - 1))) + 1.0f) * 0.5f );
			aoVertices[ r * cols + c ].colour   = glm::vec4( v3colour , 1.0f );
		}
	}

	// defining index count based off quad count (2 triangles per quad)
	unsigned int* auiIndices = new unsigned int[ (rows - 1) * (cols - 1) * 6 ];
	
	unsigned int index = 0;
	for ( unsigned int r = 0 ; r < (rows - 1) ; ++r )
	{
		for ( unsigned int c = 0 ; c < (cols - 1) ; ++c )
		{
			// triangle 1
			auiIndices[ index++ ] = (r + 1) * cols + (c + 1);
			auiIndices[ index++ ] = r * cols + c;
			auiIndices[ index++ ] = (r + 1) * cols + c;
			
	
			// triangle 2
			auiIndices[ index++ ] = r * cols + (c + 1);
			auiIndices[ index++ ] = r * cols + c;
			auiIndices[ index++ ] = (r + 1) * cols + (c + 1);
			
		}
	}

	// create and bind buffers to a vertex array object
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);
	
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray( m_VAO );

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, (rows * cols) * sizeof(V_4v_4c), aoVertices, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(V_4v_4c), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(V_4v_4c), ((char*)0) + 16);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (rows - 1) * (cols - 1) * 6 * sizeof(unsigned int), auiIndices, GL_STATIC_DRAW);
	
	glBindVertexArray(0);
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

	delete[] aoVertices;
	delete[] auiIndices;
}