#pragma once

#include <map>
#include <memory>
#include "spdlog/spdlog.h"
#include "../Defines.h"

enum LogLevel
{
    trace,
    info,
    debug,
    warn,
    error,
    critical
};

class LogManager
{
public:
    static void InitLogger();
    static uint64_t GetEngineLogger() { return _engineLogger; }
    static uint64_t GetAppLogger() { return _appLogger; }

    static bool GetLogger(uint64_t id,std::shared_ptr<spdlog::logger>& logger);
    static void SendMessageToLogger(uint64_t id,LogLevel level,const char* message);
private:
    static uint64_t CreateLogger(const char* name,LogLevel minLevel);
    static uint64_t GenLoggerID();

    static std::map<uint64_t,std::shared_ptr<spdlog::logger>> loggers;

    static uint64_t _engineLogger;
    static uint64_t _appLogger;
};

#define ENGINE_TRACE(...) LogManager::SendMessageToLogger(LogManager::GetEngineLogger(),trace,__VA_ARGS__)
#define ENGINE_INFO(...) LogManager::SendMessageToLogger(LogManager::GetEngineLogger(),info,__VA_ARGS__)
#define ENGINE_DEBUG(...) LogManager::SendMessageToLogger(LogManager::GetEngineLogger(),debug,__VA_ARGS__)
#define ENGINE_WARN(...) LogManager::SendMessageToLogger(LogManager::GetEngineLogger(),warn,__VA_ARGS__)
#define ENGINE_ERROR(...) LogManager::SendMessageToLogger(LogManager::GetEngineLogger(),error,__VA_ARGS__)
#define ENGINE_CRITICAL(...) LogManager::SendMessageToLogger(LogManager::GetEngineLogger(),critical,__VA_ARGS__)

#define APP_TRACE(...) LogManager::SendMessageToLogger(LogManager::GetAppLogger(),trace,__VA_ARGS__)
#define APP_INFO(...) LogManager::SendMessageToLogger(LogManager::GetAppLogger(),info,__VA_ARGS__)
#define APP_DEBUG(...) LogManager::SendMessageToLogger(LogManager::GetAppLogger(),debug,__VA_ARGS__)
#define APP_WARN(...) LogManager::SendMessageToLogger(LogManager::GetAppLogger(),warn,__VA_ARGS__)
#define APP_ERROR(...) LogManager::SendMessageToLogger(LogManager::GetAppLogger(),error,__VA_ARGS__)
#define APP_CRITICAL(...) LogManager::SendMessageToLogger(LogManager::GetAppLogger(),critical,__VA_ARGS__)


