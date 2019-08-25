#include "OGLEngine2.h"
#include "GL/glew.h"

class Quad
{
public:
	Vector2 position;

private:
	unsigned int indices[6];
	Vector2 vertices[4];
	Vector2 transformedVertices[4];

public:
	Quad(Vector2 one, Vector2 two, Vector2 three, Vector2 four)
		: position(Vector2(0.0f, 0.0f)),
		indices{0, 1, 2, 2, 3, 0},
		vertices{ one, two, three, four },
		transformedVertices{ Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f) }
	{
		TransformVertices();
	}

	float* GetPositions()
	{
		return (float*)((Vector2*)transformedVertices);
	}

	unsigned int* GetIndices()
	{
		return indices;
	}

	void Move(Vector2 direction)
	{
		position += direction;
		TransformVertices();
	}

private:
	void TransformVertices()
	{
		for (int i = 0; i < 4; i++) transformedVertices[i] = vertices[i] + position;
	}
};

class TestApplication : public Application
{
private:
	Quad quad;
	unsigned int buffer;
	unsigned int indexBuffer;
	unsigned int vertexArray;
	unsigned int redShader;
	unsigned int blueShader;
	Vector2 step;
	Vector2 direction;
	
public:
	TestApplication() : quad(Quad(Vector2(-0.5f, -0.5f),
								  Vector2(0.5f, -0.5f),
								  Vector2(0.5f, 0.5f),
								  Vector2(-0.5f, 0.5f))),
						buffer(0),
						redShader(0),
						blueShader(0),
						step(Vector2(0.01f, 0.005f)),
						direction(Vector2(step.x, step.y)) {}

	static std::tuple<std::string, std::string> ParseShader(const std::string& filePath)
	{
		std::ifstream stream(filePath);
		if (stream.fail()) Logger::LogError("%s doesn't exist\n", filePath);
		
		enum class ShaderType 
		{
			NONE = -1, VERTEX = 0, FRAGMENT = 1
		};

		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;
		while (getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos) type = ShaderType::VERTEX;
				else if (line.find("fragment") != std::string::npos) type = ShaderType::FRAGMENT;
			}
			else ss[(int)type] << line << "\n";
		}
		return { ss[0].str(), ss[1].str() };
	}

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
		glGenBuffers(1, &indexBuffer);

		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		auto[vertexShaderSource1, fragmentShaderSource1] = ParseShader("TestApplication/res/shaders/BasicRed.shader");
		redShader = CreateShader(vertexShaderSource1, fragmentShaderSource1);
		auto[vertexShaderSource2, fragmentShaderSource2] = ParseShader("TestApplication/res/shaders/BasicBlue.shader");
		blueShader = CreateShader(vertexShaderSource2, fragmentShaderSource2);

		return true;
	}

	bool OnUpdate() override
	{
		Logger::Log("Running...");
		
		if (quad.position.x > 0.5f) direction.x = -step.x;
		else if (quad.position.x < -0.5f) direction.x = step.x;
		if (quad.position.y > 0.5f) direction.y = -step.y;
		else if (quad.position.y < -0.5f) direction.y = step.y;

		quad.Move(direction);

		glClear(GL_COLOR_BUFFER_BIT);

		static float* positions = quad.GetPositions();
		static unsigned int* indices = quad.GetIndices();

		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

		glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_DYNAMIC_DRAW);
		// glBufferData(GL_ARRAY_BUFFER, size of data we're pushing, the data itself, can be static, dynamic.. see documentation);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_DYNAMIC_DRAW);
		// glBufferData(GL_ARRAY_BUFFER, size of data we're pushing, the data itself, can be static, dynamic.. see documentation);

		glEnableVertexAttribArray(0);
		// glEnableVertexAttribArray(attribute index);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
		// glVertexAttribPointer(attribute index, elements count, GL_FLOAT, normalize (for 0 .. 255 byte or smth),
		// size of vertex in bytes (includes texture coords), starting index (in bytes));

		glUseProgram(redShader);

		// glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		
		return true;
	}

	bool OnExit() override
	{
		glDeleteProgram(redShader);
		glDeleteProgram(blueShader);
		Logger::Log("Stopped TestApplication");
		return true;
	}
};

OGLEngine2::Application* OGLEngine2::CreateApplication()
{
	return new TestApplication();
}