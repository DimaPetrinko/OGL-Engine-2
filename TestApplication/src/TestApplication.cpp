#include "OGLEngine2.h"
#include "GL/glew.h"

#ifdef PLATFORM_WIN64
#define WORKING_DIRECTORY ""
#elif PLATFORM_LINUX64
#define WORKING_DIRECTORY "TestApplication/"
#endif

#define GlCall(x) x;\
while (unsigned int error = glGetError())\
Logger::LogError("(" + std::to_string(error) + ") in " + #x + " " + __FILE__ + ":" + std::to_string(__LINE__));

class Quad
{
public:
	Vector2 position;

private:
	unsigned int indices[6];
	Vector2 vertices[4];
	Vector2 transformedVertices[4];

public:
	Quad(const Vector2& one, const Vector2& two, const Vector2& three, const Vector2& four)
		: position(Vector2(0.0f, 0.0f)),
		indices{0, 1, 2, 2, 3, 0},
		vertices{ one, two, three, four },
		transformedVertices{ Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f) }
	{
		TransformVertices();
	}

	float* GetPositions()
	{
		return (float*)(Vector2*)transformedVertices;
	}

	unsigned int* GetIndices()
	{
		return indices;
	}

	void Move(const Vector2& direction)
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
	unsigned int buffer{};
	unsigned int ibo{};
	unsigned int vao{};
	unsigned int basicShader{};
	int colorUniformLocation{};
	int mvpUniformLocation{};
	Vector2 step;
	Vector2 direction;
	
public:
	TestApplication() : quad(Quad(Vector2(-50.0f, -50.0f),
								  Vector2(50.0f, -50.0f),
								  Vector2(50.0f, 50.0f),
								  Vector2(-50.0f, 50.0f))),
						step(Vector2(20.f, 5.f)),
						direction(Vector2(step.x, step.y)) {}

	static std::tuple<std::string, std::string> ParseShader(const std::string& filePath)
	{
		std::ifstream stream(filePath);
		if (stream.fail()) Logger::LogError("%s doesn't exist\n", filePath);
		
		enum class ShaderType 
		{
			None = -1, Vertex = 0, Fragment = 1
		};

		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::None;
		while (getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos) type = ShaderType::Vertex;
				else if (line.find("fragment") != std::string::npos) type = ShaderType::Fragment;
			}
			else ss[(int)type] << line << "\n";
		}
		return { ss[0].str(), ss[1].str() };
	}

	static unsigned int CompileShader(unsigned int type, const std::string& source)
	{
		unsigned int id = GlCall(glCreateShader(type));
		const char* src = source.c_str();
		GlCall(glShaderSource(id, 1, &src, nullptr));
		GlCall(glCompileShader(id));

		int result;
		GlCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
		if (result == GL_FALSE)
		{
			int length;
			GlCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
			char* message = (char*)alloca(length * sizeof(char));
			GlCall(glGetShaderInfoLog(id, length, &length, message));
			Logger::LogError("Failed to compile shader! %s\n", message);
			GlCall(glDeleteShader(id));
			return 0;
		}

		return id;
	}

	static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		unsigned int program = GlCall(glCreateProgram());
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
		GlCall(glAttachShader(program, vs));
		GlCall(glAttachShader(program, fs));
		GlCall(glLinkProgram(program));
		GlCall(glValidateProgram(program));

		GlCall(glDeleteShader(vs));
		GlCall(glDeleteShader(fs));

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

		GlCall(glGenVertexArrays(1, &vao));
		GlCall(glGenBuffers(1, &buffer));
		GlCall(glGenBuffers(1, &ibo));

		GlCall(glBindVertexArray(vao));
		
		GlCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
		GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
		GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), quad.GetIndices(), GL_DYNAMIC_DRAW));
		GlCall(glEnableVertexAttribArray(0));
		GlCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr));
		// glVertexAttribPointer(attribute index, elements count, GL_FLOAT, normalize (for 0 .. 255 byte or smth),
		// size of vertex in bytes (includes texture coords), starting index (in bytes));

		GlCall(glBindVertexArray(0));

		GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
		GlCall(glUseProgram(0));

		auto[vertexShaderSource, fragmentShaderSource] = ParseShader(WORKING_DIRECTORY "res/shaders/Basic.shader");
		basicShader = CreateShader(vertexShaderSource, fragmentShaderSource);
		colorUniformLocation = GlCall(glGetUniformLocation(basicShader, "u_color"));
		mvpUniformLocation = GlCall(glGetUniformLocation(basicShader, "u_mvp"));

		return true;
	}

	bool OnUpdate() override
	{
		// Logger::Log("Running...");
		
		auto w = (float)window->GetWidth();
		auto h = (float)window->GetHeight();

		if (quad.position.x > w) direction.x = -step.x;
		else if (quad.position.x < 0) direction.x = step.x;
		if (quad.position.y > h) direction.y = -step.y;
		else if (quad.position.y < 0) direction.y = step.y;

		quad.Move(direction);

		static float* positions = quad.GetPositions();
		static unsigned int* indices = quad.GetIndices();
		Vector2 positionNormalized = quad.position.Normalized();

		GlCall(glClear(GL_COLOR_BUFFER_BIT));

		GlCall(glUseProgram(basicShader));
		GlCall(glUniform4f(colorUniformLocation, positionNormalized.x, 10.0f, positionNormalized.y, 1.0f));
		
		float mvpMatrix[16] =
		{
			2/w,0,	0,	-1,
			0,	2/h,0,	-1,
			0,	0,	1,	0,
			0,	0,	0,	 1,
		};
		GlCall(glUniformMatrix4fv(mvpUniformLocation, 1, GL_TRUE, mvpMatrix));

		GlCall(glBindVertexArray(vao));
		GlCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
		GlCall(glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_DYNAMIC_DRAW));
		// glBufferData(GL_ARRAY_BUFFER, size of data we're pushing, the data itself, can be static, dynamic.. see documentation);
		GlCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
		GlCall(glBindVertexArray(0));

		return true;
	}

	bool OnExit() override
	{
		GlCall(glDeleteProgram(basicShader));
		Logger::Log("Stopped TestApplication");
		return true;
	}
};

OGLEngine2::Application* OGLEngine2::CreateApplication()
{
	return new TestApplication();
}