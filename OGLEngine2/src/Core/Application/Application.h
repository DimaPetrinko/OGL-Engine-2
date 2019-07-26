#pragma once

namespace OGLEngine2
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		virtual bool OnStart() = 0;
		virtual bool OnUpdate() = 0;
		virtual bool OnExit() = 0;

		void Run();
	};

	Application* CreateApplication();
}