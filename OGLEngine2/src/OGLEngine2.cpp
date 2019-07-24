#include <iostream>
#include "OGLEngine2.h"

Application::Application()
{
}

Application::~Application()
{
}

void Application::Start()
{
	std::cout << "Called at the start\n";
}

void Application::Update()
{
	std::cout << "Called every frame\n";
}

void Application::Stop()
{
	std::cout << "Called at the end\n";
}
