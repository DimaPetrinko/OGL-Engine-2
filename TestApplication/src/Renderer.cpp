#include "GL/glew.h"
#include "OGLEpch.h"
#include "Renderer.h"

void GLClearError() { while (glGetError() != GL_NO_ERROR); }

bool GLLogCall(const char* function, const char* file, int line)
{
	while (auto error = glGetError())
	{
		OGLEngine2::Logger::LogError("[OpenGL] " + std::to_string(error) + " in " + function + " " + file + ":" + std::to_string(line));
		return false;
	}
	return true;
}
