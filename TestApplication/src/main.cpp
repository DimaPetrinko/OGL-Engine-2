#include <iostream>
#include "../../OGLEngine2/include/OGLEngine2.h"

class TestApplication : public Application {};

int main()
{
	TestApplication* application = new TestApplication();

	application->Start();

	while (true)
	{
		application->Update();
	}

	application->Stop();

	delete application;
}