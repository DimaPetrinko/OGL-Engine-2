#pragma once

#include <iostream>

namespace OGLEngine2
{
	class Logger
	{
	public:
		Logger();
		~Logger();

		static void Log(const char* message);
		static void LogWarning(const char* message);
		static void LogError(const char* message);
	};
}