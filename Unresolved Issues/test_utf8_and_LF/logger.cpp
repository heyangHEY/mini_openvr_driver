#include "logger.hpp"
#include "assert.hpp"

std::shared_ptr<spdlog::logger> logger;

// logger_level: "trace", "debug", "info", "warning", "error", "critical", "off"  
void build_logger(const std::string &logger_name, const std::string &logger_level, const std::string &log_file_path)
{
	try {
		// Create a file rotating logger with 5mb size max and 5 rotated files
		auto max_size = 5 * 1024 * 1024;
		auto max_files = 5;
		bool rotate_on_open = true;
		// 如果设置为true，那么在日志器打开日志文件进行写入操作时，会立即进行一次日志轮转
		// 如果设置为false，那么只有在写入操作导致日志文件大小超过最大限制时，才会进行日志轮转。如果没超过最大限制，即是日志中有历史日志，也会继续在下面写入。
		// 为false时，一个日志文件可能会堆叠多次历史写入。
		logger = spdlog::rotating_logger_mt("logger", log_file_path.c_str(), max_size, max_files, rotate_on_open);
		// auto logger = spdlog::stdout_color_mt("logger");
	} catch (const spdlog::spdlog_ex& ex) {
		// Handle exceptions
		std::cerr << "error: Logger initialization failed: " << ex.what() << std::endl;
	}

	ASSERT_WITH_MSG(logger.get() != nullptr, "Pointer[logger.get()] is nullptr.");

	// Set the logger format
	// %Y-%m-%d %H:%M:%S.%e: 年-月-日 时:分:秒.毫秒 
	// %^: start color range
	// %$: end color range
	// %l: 日志级别
	// %L: 日志级别简称
	// %@: 文件名与行数
	// %s: 文件名
	// %g: 文件名（含路径）
	// %#: 行数
	// %!: 函数名
	// %v: 日志内容
	logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] [%s:%#] %v");
	logger->set_level(spdlog::level::from_str(logger_level));
	logger->flush_on(spdlog::level::debug); // TODO

	SPDLOG_LOGGER_INFO(logger, "logger initialization successfully");
	logger->flush();
}

std::shared_ptr<spdlog::logger> get_logger()
{
	ASSERT_WITH_MSG(logger.get() != nullptr, "Pointer[logger.get()] is nullptr.");
	return logger;
}

// logger_level: "trace", "debug", "info", "warning", "error", "critical", "off" 
// SPDLOG_LOGGER_TRACE(logger, ...);
// SPDLOG_LOGGER_DEBUG(logger, ...);
// SPDLOG_LOGGER_INFO(logger, ...);
// SPDLOG_LOGGER_WARN(logger, ...);
// SPDLOG_LOGGER_ERROR(logger, ...);
// SPDLOG_LOGGER_CRITICAL(logger, ...);