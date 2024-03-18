#pragma once

#ifdef CORE_API_EXPORTS
#define CORE_API __declspec(dllexport)
#else
#define CORE_API __declspec(dllimport)

#endif

#ifndef Logger_H
#define Logger_H

#include <string>
#include <deque>

#include <map>
#include <vector>

#include <numeric>
#include <algorithm>
#include <memory>

#include <iostream>
#include <fstream>
#include <sstream>


template<typename T = double>


class CORE_API Logger {
public:

    Logger();
    ~Logger();

    enum class LogLevel {
        Error,
        Warning,
        Info,
        Debug,
        Input,
        Clear,
        Destroy
    };

    struct LogEntry {
        LogLevel level;
        std::string message;
        T Num;
    };

    void Log(LogLevel level, const std::string& message, T Num, const char* file = nullptr, int line = -1);


    const std::deque<LogEntry>& GetLogs() const;

    void Info(const std::string& message, T Num = T());
    void Error(const std::string& message, T Num, const char* file, int line);
    void Warning(const std::string& message, T Num, const char* file, int line);
    void Debug(const std::string& message, T Num = T());
    void Input(const std::string& message, T Num = T());
    void Clear(const std::string& message, T Num = T());
    void Destroy(const std::string& message, T Num = T());


private:
    std::deque<LogEntry> logs;
    const size_t maxLogCount = 100;
};

#endif // Logger_H
