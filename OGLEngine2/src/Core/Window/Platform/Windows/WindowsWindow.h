#pragma once

#include <OGLEpch.h>
#include "Core/Window/Window.h"
#include "GLFW/glfw3.h"

namespace OGLEngine2
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowData& data);
		virtual ~WindowsWindow();

		bool OnUpdate() override;

		inline unsigned int GetWidth() const override { return data.width; }
		inline unsigned int GetHeight() const override { return data.height; }

	private:
		virtual void Init(const WindowData& data);
		virtual void Shutdown();

	private:
		GLFWwindow* window;

		WindowData data;
	};
}