#pragma once

namespace OGLEngine2
{
	class Logger
	{
	private:
		inline static const std::string INFO_STRING = "[Info]: ";
		inline static const std::string WARNING_STRING = "[Warning]: ";
		inline static const std::string ERROR_STRING = "[Error]: ";
		
	public:
		Logger();
		~Logger();

		static void Log(const char* const message);
		static void Log(const std::string& message);
		static void Log(const unsigned char* const message);
		static void Log(const std::string&, const char* message);
		static void Log(const std::string&, const std::string& message);
		static void Log(const std::string&, const unsigned char* message);
		
		static void LogWarning(const char* message);
		static void LogWarning(const std::string& message);
		static void LogWarning(const unsigned char* message);
		static void LogWarning(const std::string&, const char* message);
		static void LogWarning(const std::string&, const std::string& message);
		static void LogWarning(const std::string&, const unsigned char* message);
		
		static void LogError(const char* message);
		static void LogError(const std::string& message);
		static void LogError(const unsigned char* message);
		static void LogError(const std::string&, const char* message);
		static void LogError(const std::string&, const std::string& message);
		static void LogError(const std::string&, const unsigned char* message);

	private:
		static void LogInternal(const std::string&, const char* message);
		static void LogInternal(const std::string&, const std::string& message);
		static void LogInternal(const std::string&, const unsigned char* message);
	};
}