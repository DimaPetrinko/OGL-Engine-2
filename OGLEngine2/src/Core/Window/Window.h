#pragma once

namespace OGLEngine2
{
	struct WindowData
	{
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowData(std::string title = "OGL Engine 2", const unsigned int width = 1280, const unsigned int height = 720)
			: title(std::move(title)), width(width), height(height) {}

		void CopyTo(WindowData*other) const
		{
			other->width = height;
			other->height = height;
			other->title = title;
		}

		void CopyFrom(const WindowData& other)
		{
			title = other.title;
			height = other.height;
			width = other.width;
		}
	};

	class Window
	{
	public:
		virtual ~Window() = default;

		virtual bool OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		static Window* Create(const WindowData& data = WindowData());
	};
}