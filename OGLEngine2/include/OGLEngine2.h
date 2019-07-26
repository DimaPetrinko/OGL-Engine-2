#pragma once

namespace OGLEngine2
{
	class Application
	{
	public:
		Application();
		~Application();
	private:

	public:
		virtual void Start();
		virtual void Update();
		virtual void Stop();
	};
}