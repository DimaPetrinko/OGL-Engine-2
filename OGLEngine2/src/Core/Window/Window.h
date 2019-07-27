#pragma once

namespace OGLEngine2
{
	struct WindowData
	{
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowData(const std::string& title = "OGL Engine 2", unsigned int width = 1280, unsigned int height = 720)
			: title(title), width(width), height(height) {}
	};

	class Window
	{
	public:
		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		static Window* Create(const WindowData& data = WindowData());
	};
}