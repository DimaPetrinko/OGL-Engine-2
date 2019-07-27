#include <OGLEpch.h>

namespace OGLEngine2
{
	Logger::Logger() {}
	Logger::~Logger() {}

	void Logger::Log(const std::string& message)
	{
		std::cout << "[Info]: " << message << "\n";
	}

	void Logger::LogWarning(const std::string& message)
	{
		std::cout << "[Warning]: " << message << "\n";
	}

	void Logger::LogError(const std::string& message)
	{
		std::cout << "[Error]: " << message << "\n";
	}
}