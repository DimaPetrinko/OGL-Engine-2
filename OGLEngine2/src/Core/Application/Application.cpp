#include <iostream>
#include "Application.h"

namespace OGLEngine2
{
	Application::Application() {}

	Application::~Application() {}

	void Application::Run()
	{
		if (!OnStart()) return;
		while (OnUpdate());
		OnExit();
	}
}