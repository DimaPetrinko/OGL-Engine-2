#pragma once

namespace OGLEngine2
{
	class Logger
	{
	public:
		Logger();
		~Logger();

		static void Log(const std::string& message);
		static void LogWarning(const std::string& message);
		static void LogError(const std::string& message);
	};
}