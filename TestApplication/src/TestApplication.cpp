#include <iostream>
#include "OGLEngine2.h"

class TestApplication : public OGLEngine2::Application
{
public:
	bool OnStart() override
	{
		OGLEngine2::Logger::Log("Started\n");
		return true;
	}

	bool OnUpdate() override
	{
		OGLEngine2::Logger::Log("Running...");
		return true;
	}

	bool OnExit() override
	{
		OGLEngine2::Logger::Log("Stopped\n");
		return true;
	}
};

OGLEngine2::Application* OGLEngine2::CreateApplication()
{
	return new TestApplication();
}