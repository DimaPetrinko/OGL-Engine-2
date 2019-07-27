#include <OGLEpch.h>
#include "Application.h"

namespace OGLEngine2
{
	Application::Application()
	{
		window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {}

	void Application::Run()
	{
		if (!OnStart()) return;
		running = true;
		while (running)
		{
			window->OnUpdate();
			running = OnUpdate();
		}
		OnExit();
	}
}