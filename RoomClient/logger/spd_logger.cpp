/**
 * This file is part of mediasoup_client project.
 * Author:    Jackie Ou
 * Created:   2021-11-01
 **/

#include "spd_logger.h"
#include <memory>
#include "spdlog/cfg/env.h"
#include "spdlog/logger.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/async.h"
#include "spdlog/sinks/msvc_sink.h"
#include "rtc_log_sink.h"
#include "rtc_base/logging.h"

namespace vi {

    std::shared_ptr<spdlog::logger> Logger::_appLogger;

    std::shared_ptr<spdlog::logger> Logger::_rtcLogger;

    std::unique_ptr<RTCLogSink> Logger::_rtcLogSink;

    Logger::Logger()
	{

	}

    Logger::~Logger()
	{
		destroy();
	}

    void Logger::init()
	{
        spdlog::cfg::load_env_levels();

        spdlog::init_thread_pool(32768, 3);

		std::string pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] [%t] [%s:%#] [%!] %v");

        auto consoleSink = std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>();
        consoleSink->set_level(spdlog::level::trace);
        consoleSink->set_pattern(pattern);

        _appLogger = spdlog::create_async_nb<spdlog::sinks::rotating_file_sink_mt, std::string, size_t, size_t>("app", "./logs/app.log", 1024 * 1024 * 5, 5);
		_appLogger->set_level(spdlog::level::trace);
		_appLogger->set_pattern(pattern);
        _appLogger->sinks().emplace_back(consoleSink);

        _rtcLogger = spdlog::create_async_nb<spdlog::sinks::rotating_file_sink_mt, std::string, size_t, size_t>("rtc", "./logs/rtc.log", 1024 * 1024 * 5, 3);
		_rtcLogger->set_level(spdlog::level::trace);

		if (!_rtcLogSink) {
			_rtcLogSink = std::make_unique<RTCLogSink>();
			rtc::LogMessage::SetLogToStderr(false);
			rtc::LogMessage::AddLogToStream(_rtcLogSink.get(), rtc::LS_VERBOSE);
		}
	}

    void Logger::destroy()
	{
		_rtcLogger->flush();
		_appLogger->flush();
		spdlog::drop_all();

		if (_rtcLogSink) {
			rtc::LogMessage::RemoveLogToStream(_rtcLogSink.get());
		}
	}

    std::shared_ptr<spdlog::logger>& Logger::rtcLogger()
	{
		return _rtcLogger;
	}

    std::shared_ptr<spdlog::logger>& Logger::appLogger()
	{
		return _appLogger;
	}

}
