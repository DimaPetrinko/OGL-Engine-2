#include "Logger.h"

namespace OGLEngine2
{
	Logger::Logger() {}
	Logger::~Logger() {}

	void Logger::Log(const char* message)
	{
		std::cout << "[Info]: " << message << "\n";
	}

	void Logger::LogWarning(const char* message)
	{
		std::cout << "[Warning]: " << message << "\n";
	}

	void Logger::LogError(const char* message)
	{
		std::cout << "[Error]: " << message << "\n";
	}
}