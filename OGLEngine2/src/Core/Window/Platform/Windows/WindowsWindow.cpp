#include <OGLEpch.h>
#include "Core/Logging/Logger.h"
#include "WindowsWindow.h"

namespace OGLEngine2
{
	static bool glfwInitialized = false;

	Window* Window::Create(const WindowData& data)
	{
		return new WindowsWindow(data);
	}

	WindowsWindow::WindowsWindow(const WindowData& data)
	{
		Init(data);
	}

	WindowsWindow::~WindowsWindow() 
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowData& data)
	{
		this->data.title = data.title;
		this->data.width = data.width;
		this->data.height = data.height;

		Logger::Log("Creating new window " + data.title + " (" + std::to_string(data.width)
			+ ", " + std::to_string(data.height) + ")");

		if (!glfwInitialized)
		{
			int success = glfwInit();
			// TODO: make a macro
			if (!success)
			{
				Logger::LogError("Could not initialize GLFW!");
				return;
			}
			glfwInitialized = true;
		}

		window = glfwCreateWindow(data.width, data.height, data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, &(this->data));
		glfwSwapInterval(1);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}