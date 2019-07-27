#pragma once

extern OGLEngine2::Application* OGLEngine2::CreateApplication();

int main(int argc, char** argv)
{
	auto application = OGLEngine2::CreateApplication();
	application->Run();
	delete application;
}