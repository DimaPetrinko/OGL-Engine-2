#include <iostream>
#include "OGLEngine2.h"

class TestApplication : public OGLEngine2::Application
{
public:
	bool OnStart() override
	{
		std::cout << "Started\n";
		return true;
	}

	bool OnUpdate() override
	{
		std::cout << "Running...\n";
		return true;
	}

	bool OnExit() override
	{
		std::cout << "Stopped\n";
		return true;
	}
};

OGLEngine2::Application* OGLEngine2::CreateApplication()
{
	return new TestApplication();
}