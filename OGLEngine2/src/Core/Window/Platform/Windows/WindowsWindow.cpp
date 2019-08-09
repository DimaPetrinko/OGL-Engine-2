#include <OGLEpch.h>
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
		window = nullptr;
		WindowsWindow::Init(data);
	}

	WindowsWindow::~WindowsWindow() 
	{
		WindowsWindow::Shutdown();
	}

	void WindowsWindow::Init(const WindowData& data)
	{
		this->data.title = data.title;
		this->data.width = data.width;
		this->data.height = data.height;

		if (!glfwInitialized)
		{
			auto success = glfwInit();
			// TODO: make a macro
			if (!success)
			{
				Logger::LogError("Could not initialize GLFW!");
				return;
			}
			glfwInitialized = true;
			Logger::Log("Initialized GLFW");
		}

		window = glfwCreateWindow(data.width, data.height, data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, &(this->data));
		glfwSwapInterval(1);

		Logger::Log("Created new window " + data.title + " (" + std::to_string(data.width)
			+ ", " + std::to_string(data.height) + ")");
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(window);
	}

	bool WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
		return !glfwWindowShouldClose(window);
	}
}