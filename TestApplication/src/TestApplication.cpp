#include "OGLEngine2.h"

class TestApplication : public Application
{
public:
	bool OnStart() override
	{
		Logger::Log("Started TestApplication");
		return true;
	}

	bool OnUpdate() override
	{
		Logger::Log("Running...");
		return true;
	}

	bool OnExit() override
	{
		Logger::Log("Stopped TestApplication");
		return true;
	}
};

OGLEngine2::Application* OGLEngine2::CreateApplication()
{
	return new TestApplication();
}