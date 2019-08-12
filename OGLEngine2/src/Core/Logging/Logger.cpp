#include <OGLEpch.h>

namespace OGLEngine2
{
	Logger::Logger() = default;
	Logger::~Logger() = default;

	void Logger::Log(const char* const message)
	{
		Log("%s\n", message);
	}	
	void Logger::Log(const std::string& message)
	{
		Log("%s\n", message);
	}
	void Logger::Log(const unsigned char* const message)
	{
		Log("%s\n", message);
	}
	void Logger::Log(const std::string& format, const char* const message)
	{
		LogInternal(INFO_STRING + format, message);
	}
	void Logger::Log(const std::string& format, const std::string& message)
	{
		LogInternal(INFO_STRING + format, message.c_str());
	}
	void Logger::Log(const std::string& format, const unsigned char* const message)
	{
		LogInternal(INFO_STRING + format, message);
	}

	void Logger::LogWarning(const char* const message)
	{
		LogWarning("%s\n", message);
	}
	void Logger::LogWarning(const std::string& message)
	{
		LogWarning("%s\n", message);
	}
	void Logger::LogWarning(const unsigned char* const message)
	{
		LogWarning("%s\n", message);
	}
	void Logger::LogWarning(const std::string& format, const char* const message)
	{
		LogInternal(WARNING_STRING + format, message);
	}
	void Logger::LogWarning(const std::string& format, const std::string& message)
	{
		LogInternal(WARNING_STRING + format, message.c_str());
	}
	void Logger::LogWarning(const std::string& format, const unsigned char* const message)
	{
		LogInternal(WARNING_STRING + format, message);
	}

	void Logger::LogError(const char* const message)
	{
		LogError("%s\n", message);
	}
	void Logger::LogError(const std::string& message)
	{
		LogError("%s\n", message);
	}
	void Logger::LogError(const unsigned char* const message)
	{
		LogError("%s\n", message);
	}
	void Logger::LogError(const std::string& format, const char* const message)
	{
		LogInternal(ERROR_STRING + format, message);
	}
	void Logger::LogError(const std::string& format, const std::string& message)
	{
		LogInternal(ERROR_STRING + format, message.c_str());
	}
	void Logger::LogError(const std::string& format, const unsigned char* const message)
	{
		LogInternal(ERROR_STRING + format, message);
	}

	void Logger::LogInternal(const std::string& format, const char* const message)
	{
		printf(format.c_str(), message);
	}
	void Logger::LogInternal(const std::string& format, const std::string& message)
	{
		printf(format.c_str(), message.c_str());
	}
	void Logger::LogInternal(const std::string& format, const unsigned char* const message)
	{
		printf(format.c_str(), message);
	}
}