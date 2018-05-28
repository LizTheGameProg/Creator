//#include "openGLBindings.h"
//
//PFNGLUSEPROGRAMPROC					glUseProgram				;
//PFNGLCREATESHADERPROC				glCreateShader				;
//PFNGLSHADERSOURCEPROC				glShaderSource				;
//PFNGLCOMPILESHADERPROC				glCompileShader				;
//PFNGLCREATEPROGRAMPROC				glCreateProgram				;
//PFNGLATTACHSHADERPROC				glAttachShader				;
//PFNGLLINKPROGRAMPROC				glLinkProgram				;
//PFNGLDELETESHADERPROC				glDeleteShader				;
//PFNGLDELETEPROGRAMPROC				glDeleteProgram				;
//PFNGLDELETEBUFFERSPROC				glDeleteBuffers				;
//PFNGLDELETEVERTEXARRAYSPROC			glDeleteVertexArrays		;
//PFNGLBINDBUFFERPROC					glBindBuffer				;
//PFNGLBUFFERDATAPROC					glBufferData				;
//PFNGLGETUNIFORMLOCATIONPROC			glGetUniformLocation		;
//PFNGLUNIFORMMATRIX4FVPROC			glUniformMatrix4fv			;
//PFNGLACTIVETEXTUREPROC				glActiveTexture				;
//PFNGLUNIFORM1IPROC					glUniform1i					;
//PFNGLBINDVERTEXARRAYPROC			glBindVertexArray			;
//PFNGLGENVERTEXARRAYSPROC			glGenVertexArrays			;
//PFNGLGENBUFFERSPROC					glGenBuffers				;
//PFNGLENABLEVERTEXATTRIBARRAYPROC	glEnableVertexAttribArray	;
//PFNGLVERTEXATTRIBPOINTERPROC		glVertexAttribPointer		;
//PFNGLBINDATTRIBLOCATIONPROC			glBindAttribLocation		;
//PFNGLGETPROGRAMIVPROC				glGetProgramiv				;
//PFNGLGETSHADERIVPROC				glGetShaderiv				;
//PFNGLGETSHADERINFOLOGPROC			glGetShaderInfoLog			;
//PFNGLBUFFERSUBDATAPROC				glBufferSubData				;
//
//void openGLBindings::init()
//{
//	glUseProgram				= (PFNGLUSEPROGRAMPROC)					getOpenGLProcAddress("glUseProgram"					);
//	glCreateShader				= (PFNGLCREATESHADERPROC)				getOpenGLProcAddress("glCreateShader"				);
//	glShaderSource				= (PFNGLSHADERSOURCEPROC)				getOpenGLProcAddress("glShaderSource"				);
//	glCompileShader				= (PFNGLCOMPILESHADERPROC)				getOpenGLProcAddress("glCompileShader"				);
//	glCreateProgram				= (PFNGLCREATEPROGRAMPROC)				getOpenGLProcAddress("glCreateProgram"				);
//	glAttachShader				= (PFNGLATTACHSHADERPROC)				getOpenGLProcAddress("glAttachShader"				);
//	glLinkProgram				= (PFNGLLINKPROGRAMPROC)				getOpenGLProcAddress("glLinkProgram"				);
//	glDeleteShader				= (PFNGLDELETESHADERPROC)				getOpenGLProcAddress("glDeleteShader"				);
//	glDeleteProgram				= (PFNGLDELETEPROGRAMPROC)				getOpenGLProcAddress("glDeleteProgram"				);
//	glDeleteBuffers				= (PFNGLDELETEBUFFERSPROC)				getOpenGLProcAddress("glDeleteBuffers"				);
//	glDeleteVertexArrays		= (PFNGLDELETEVERTEXARRAYSPROC)			getOpenGLProcAddress("glDeleteVertexArrays"			);
//	glBindBuffer				= (PFNGLBINDBUFFERPROC)					getOpenGLProcAddress("glBindBuffer"					);
//	glBufferData				= (PFNGLBUFFERDATAPROC)					getOpenGLProcAddress("glBufferData"					);
//	glGetUniformLocation		= (PFNGLGETUNIFORMLOCATIONPROC)			getOpenGLProcAddress("glGetUniformLocation"			);
//	glUniformMatrix4fv			= (PFNGLUNIFORMMATRIX4FVPROC)			getOpenGLProcAddress("glUniformMatrix4fv"			);
//	glActiveTexture				= (PFNGLACTIVETEXTUREPROC)				getOpenGLProcAddress("glActiveTexture"				);
//	glUniform1i					= (PFNGLUNIFORM1IPROC)					getOpenGLProcAddress("glUniform1i"					);
//	glBindVertexArray			= (PFNGLBINDVERTEXARRAYPROC)			getOpenGLProcAddress("glBindVertexArray"			);
//	glGenVertexArrays			= (PFNGLGENVERTEXARRAYSPROC)			getOpenGLProcAddress("glGenVertexArrays"			);
//	glGenBuffers				= (PFNGLGENBUFFERSPROC)					getOpenGLProcAddress("glGenBuffers"					);
//	glEnableVertexAttribArray	= (PFNGLENABLEVERTEXATTRIBARRAYPROC)	getOpenGLProcAddress("glEnableVertexAttribArray"	);
//	glVertexAttribPointer		= (PFNGLVERTEXATTRIBPOINTERPROC)		getOpenGLProcAddress("glVertexAttribPointer"		);
//	glBindAttribLocation		= (PFNGLBINDATTRIBLOCATIONPROC)			getOpenGLProcAddress("glBindAttribLocation"			);
//	glGetProgramiv				= (PFNGLGETPROGRAMIVPROC)				getOpenGLProcAddress("glGetProgramiv"				);
//	glGetShaderiv				= (PFNGLGETSHADERIVPROC)				getOpenGLProcAddress("glGetShaderiv"				);
//	glGetShaderInfoLog			= (PFNGLGETSHADERINFOLOGPROC)			getOpenGLProcAddress("glGetShaderInfoLog"			);
//	glBufferSubData				= (PFNGLBUFFERSUBDATAPROC)				getOpenGLProcAddress("glBufferSubData"				);
//}
//
//void * openGLBindings::getOpenGLProcAddress(const char * name)
//{
//	void * p = (void *) wglGetProcAddress(name);
//	if(p == 0 ||				// if p == NULL
//		(p == (void*) 0x1) ||	// if p == 1
//		(p == (void*) 0x2) ||	// if p == 2
//		(p == (void*) 0x3) ||	// if p == 3
//		(p == (void*) -1))		// if p == -1
//	{
//		static HMODULE module = LoadLibraryA("opengl32.dll");
//		p = (void *) GetProcAddress(module, name);
//	}
//
//	return p;
//}