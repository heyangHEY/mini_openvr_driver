#pragma once

// ! #define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE 是在设置编译时的日志等级
// ! 默认是 SPDLOG_LEVEL_INFO，编译时会导致 SPDLOG_LOGGER_TRACE 和 SPDLOG_LOGGER_DEBUG 失效，为此得手动设置成 SPDLOG_LEVEL_TRACE
// ! 运行的日志等级可以通过 set_level() 调整
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
// TODO 编译时在cmakelists.txt中指定level，代码稳定后可提高level以提升性能

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h> // stdout_color_mt()
#include <spdlog/sinks/rotating_file_sink.h> // rotating_logger_mt()
#include <iostream>

#define LOG_T(...) SPDLOG_LOGGER_TRACE(get_logger(), __VA_ARGS__)
#define LOG_D(...) SPDLOG_LOGGER_DEBUG(get_logger(), __VA_ARGS__)
#define LOG_I(...) SPDLOG_LOGGER_INFO(get_logger(), __VA_ARGS__)
#define LOG_W(...) SPDLOG_LOGGER_WARN(get_logger(), __VA_ARGS__)
#define LOG_E(...) SPDLOG_LOGGER_ERROR(get_logger(), __VA_ARGS__)
#define LOG_C(...) SPDLOG_LOGGER_CRITICAL(get_logger(), __VA_ARGS__)
#define LOG_FLUSH get_logger()->flush()

// logger_level: "trace", "debug", "info", "warning", "error", "critical", "off"
// TODO 从json中读取logger_level、log_file_path
void build_logger(const std::string &logger_name, const std::string &logger_level, const std::string &log_file_path);

std::shared_ptr<spdlog::logger> get_logger();
