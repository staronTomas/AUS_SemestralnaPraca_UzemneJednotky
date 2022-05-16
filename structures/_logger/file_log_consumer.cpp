#include "file_log_consumer.h"

structures::FileLogConsumer::FileLogConsumer(const std::string& path) :
	fileStream_(path)
{
	if (!fileStream_.is_open())
		throw std::runtime_error("Failed to open file " + path);
}

void structures::FileLogConsumer::logMessage(LogType type, const std::string& message)
{
	fileStream_ << logTypeToString(type) << ';' << message << std::endl;
}

void structures::FileLogConsumer::logDuration(size_t size, DurationType duration, const std::string& message)
{
	fileStream_ << logTypeToString(LogType::Duration) << ';'
		<< size << ';'
		<< duration.count() << ';'
		<< message << ';'
		<< std::endl;
}