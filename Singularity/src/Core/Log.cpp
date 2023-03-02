#include "../../include/Core/Log.h"
#include "../../include/Core/RNG.h"
#include "spdlog/sinks/stdout_color_sinks.h"

std::map<uint64_t,std::shared_ptr<spdlog::logger>> LogManager::loggers = {};
uint64_t LogManager::_engineLogger;
uint64_t LogManager::_appLogger;

void LogManager::InitLogger()
{
    _engineLogger = CreateLogger("ENGINE",trace);
    _appLogger = CreateLogger("APP",trace);
}

void LogManager::SendMessageToLogger(uint64_t id, LogLevel level, const char* message)
{
    std::shared_ptr<spdlog::logger> logger;
    if(GetLogger(id,logger))
    {
        switch(level)
        {
            case trace:
                logger->trace(message);
                break;
            case info:
                logger->info(message);
                break;
            case debug:
                logger->debug(message);
                break;
            case warn:
                logger->warn(message);
                break;
            case error:
                logger->error(message);
                break;
            case critical:
                logger->critical(message);
                break;
        }
    }
}

uint64_t LogManager::CreateLogger(const char *name, LogLevel minLevel)
{
    spdlog::sink_ptr sinks[1];
    sinks[0] = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    sinks[0]->set_pattern("%^[%T] [%l] %n: %v%$");

    auto id = GenLoggerID();
    auto level = (spdlog::level::level_enum)minLevel;

    std::shared_ptr<spdlog::logger> logger = std::make_shared<spdlog::logger>(name,std::begin(sinks),std::end(sinks));
    register_logger(logger);
    logger->set_level(level);
    logger->flush_on(level);

    loggers.insert({id,logger});
    return id;
}

uint64_t LogManager::GenLoggerID()
{
    auto id = RNG::GetRandomUInt64();
    if(loggers.contains(id) && id > 0)
    {
        return GenLoggerID();
    }
    return id;
}

bool LogManager::GetLogger(uint64_t id, std::shared_ptr<spdlog::logger>& logger)
{
    if(id == 0 || !loggers.contains(id)) return false;

    logger = loggers[id];

    return logger != nullptr;
}
