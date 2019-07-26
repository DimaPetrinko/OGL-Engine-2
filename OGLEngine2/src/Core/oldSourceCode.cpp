// README
// To rebuild premake Ctrl+Alt+B
// To run the app - chose the correct coniguration in debug menu and press play or F5
// To manually build and run type make (or make config=debug) into the terminal
// followed by ./build/bin/PremakeProject_Debug/PremakeProject

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct Vector2
{
	float x, y;

	Vector2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	Vector2 operator+(Vector2 other)
	{
		return Vector2(x + other.x, y + other.y);
	}

	void operator+=(Vector2 other)
	{
		x += other.x;
		y += other.y;
	}
};

class Triangle
{
public:
	Vector2 position;

private:
	Vector2 vertices[3];
	Vector2 transformedVertices[3];

public:
	Triangle(Vector2 one, Vector2 two, Vector2 three)
		: vertices{ one, two, three },
		transformedVertices{ Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f) },
		position(Vector2(0.0f, 0.0f))
	{
		TransformVerticies();
	}

	float* GetPositions()
	{
		return (float*)((Vector2*)transformedVertices);
	}

	void Move(Vector2 direction)
	{
		position += direction;
		TransformVerticies();
	}

private:
	void TransformVerticies()
	{
		for (int i = 0; i < 3; i++) transformedVertices[i] = vertices[i] + position;
	}
};

int main(int argc, char** argv)
{
	GLFWwindow* window;

	if (!glfwInit()) return -1;

	window = glfwCreateWindow(800, 600, "Hello GLFW", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		std::cout << glewGetErrorString(error) << std::endl;
		return -1;
	}
	std::cout << "GL version: " << glGetString(GL_VERSION) << std::endl;

	Triangle triangle = Triangle(Vector2(-0.5f, -0.5f), Vector2(0.5f, -0.5f), Vector2(0.0f, 0.5f));
	float* positions = triangle.GetPositions();

	unsigned int buffer;
	glGenBuffers(1, &buffer);

	Vector2 step = Vector2(0.01f, 0.005f);
	Vector2 direction = Vector2(step.x, step.y);
	while (!glfwWindowShouldClose(window))
	{
		if (triangle.position.x > 0.5f) direction.x = -step.x;
		else if (triangle.position.x < -0.5f) direction.x = step.x;
		if (triangle.position.y > 0.5f) direction.y = -step.y;
		else if (triangle.position.y < -0.5f) direction.y = step.y;

		triangle.Move(direction);
		positions = triangle.GetPositions();

		glClear(GL_COLOR_BUFFER_BIT);

		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_DYNAMIC_DRAW);
		// glBufferData(GL_ARRAY_BUFFER, size of data we're pushing, the data itself, can be static, dynamic.. see documentation);

		glEnableVertexAttribArray(0);
		// glEnableVertexAttribArray(attribute index);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
		// glVertexAttribPointer(attribute index, elements count, GL_FLOAT, normalize (for 0 .. 255 byte or smth),
		// size of vertex in bytes (includes texture coords), starting index (in bytes));

		glDrawArrays(GL_TRIANGLES, 0, 3);
		// glDrawElements(GL_TRIANGLES, 3, GL_FLOAT, NULL);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}