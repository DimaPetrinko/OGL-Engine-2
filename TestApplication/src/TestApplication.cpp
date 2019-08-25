#include "OGLEngine2.h"
#include "GL/glew.h"

class Triangle
{
public:
	Vector2 position;

private:
	Vector2 vertices[3];
	Vector2 transformedVertices[3];

public:
	Triangle(Vector2 one, Vector2 two, Vector2 three)
		: position(Vector2(0.0f, 0.0f)),
		vertices{ one, two, three },
		transformedVertices{ Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f) }
	{
		TransformVertices();
	}

	float* GetPositions()
	{
		return (float*)((Vector2*)transformedVertices);
	}

	void Move(Vector2 direction)
	{
		position += direction;
		TransformVertices();
	}

private:
	void TransformVertices()
	{
		for (int i = 0; i < 3; i++) transformedVertices[i] = vertices[i] + position;
	}
};

class TestApplication : public Application
{
private:
	Triangle triangle;
	unsigned int buffer;
	unsigned int vertexArray;
	unsigned int shader;
	Vector2 step;
	Vector2 direction;
	
public:
	TestApplication() : triangle(Triangle(Vector2(-0.5f, -0.5f), Vector2(0.5f, -0.5f),
						Vector2(0.0f, 0.5f))), buffer(0), shader(0), step(Vector2(0.01f, 0.005f)),
						direction(Vector2(step.x, step.y)) {}

	static unsigned int CompileShader(unsigned int type, const std::string& source)
	{
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);
			Logger::LogError("Failed to compile shader! %s\n", message);
			glDeleteShader(id);
			return 0;
		}

		return id;
	}

	static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		unsigned int program = glCreateProgram();
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}
	
	bool OnStart() override
	{
		Logger::Log("Started TestApplication");

		auto error = glewInit();
		if (error != GLEW_OK)
		{
			Logger::Log(glewGetErrorString(error));
			return false;
		}
		Logger::Log("GL version: %s\n", glGetString(GL_VERSION));

		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);

		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		std::string vertexShaderSource =
		"#version 130\n"
		"\n"
		"in vec4 position;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	gl_Position = position;\n"
		"}\n";

		std::string fragmentShaderSource =
		"#version 130\n"
		"\n"
		"out vec4 color;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	color = vec4(0.0, 0.35, 0.55, 1.0);\n"
		"}\n";

		shader = CreateShader(vertexShaderSource, fragmentShaderSource);

		return true;
	}

	bool OnUpdate() override
	{
		Logger::Log("Running...");
		
		if (triangle.position.x > 0.5f) direction.x = -step.x;
		else if (triangle.position.x < -0.5f) direction.x = step.x;
		if (triangle.position.y > 0.5f) direction.y = -step.y;
		else if (triangle.position.y < -0.5f) direction.y = step.y;

		triangle.Move(direction);

		glClear(GL_COLOR_BUFFER_BIT);

		static float* positions = triangle.GetPositions();

		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_DYNAMIC_DRAW);
		// glBufferData(GL_ARRAY_BUFFER, size of data we're pushing, the data itself, can be static, dynamic.. see documentation);

		glEnableVertexAttribArray(0);
		// glEnableVertexAttribArray(attribute index);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
		// glVertexAttribPointer(attribute index, elements count, GL_FLOAT, normalize (for 0 .. 255 byte or smth),
		// size of vertex in bytes (includes texture coords), starting index (in bytes));

		glUseProgram(shader);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		// glDrawElements(GL_TRIANGLES, 3, GL_FLOAT, NULL);
		
		return true;
	}

	bool OnExit() override
	{
		glDeleteProgram(shader);
		Logger::Log("Stopped TestApplication");
		return true;
	}
};

OGLEngine2::Application* OGLEngine2::CreateApplication()
{
	return new TestApplication();
}