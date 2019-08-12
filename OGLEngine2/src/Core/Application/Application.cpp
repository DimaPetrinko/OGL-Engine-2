#include <OGLEpch.h>
#include "Application.h"

namespace OGLEngine2
{
	Application::Application()
	{
		Logger::Log("Initializing application");
		window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() = default;

	void Application::Run()
	{
		if (!OnStart()) return;
		running = true;
		while (running)
		{
			running = OnUpdate() && window->OnUpdate();
		}
		OnExit();
	}
}