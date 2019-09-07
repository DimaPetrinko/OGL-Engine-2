#pragma once

#include "Core/Window/Window.h"

namespace OGLEngine2
{
	class Application
	{
	public:
		Application();
		virtual ~Application() = 0;

		virtual bool OnStart() = 0;
		virtual bool OnUpdate() = 0;
		virtual bool OnExit() = 0;

		void Run();

	protected:
		std::unique_ptr<Window> window;
	private:
		bool running = false;
	};

	Application* CreateApplication();
}