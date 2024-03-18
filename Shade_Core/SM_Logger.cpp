#define CORE_API_EXPORTS

#include "SM_Logger.h"

template<typename T>
Logger<T>::Logger() {}

template<typename T>
Logger<T>::~Logger() {}

template<typename T>

void Logger<T>::Log(LogLevel level, const std::string& message, T Num, const char* file, int line) {

    LogEntry entry;
    entry.level = level;

    if (level == LogLevel::Error || level == LogLevel::Warning) {
        std::ostringstream locationInfo;
        locationInfo << "File: " << file << ", Line: " << line;
        entry.message = locationInfo.str() + " | Description: " + message;
    }
    else {
        entry.message = message;
    }

    entry.message += "| Value  " + std::to_string(Num);

    logs.push_back(entry);

    while (logs.size() > maxLogCount) {
        logs.pop_front();
    }

    switch (level) {
    case LogLevel::Error:
        std::cerr << "ERROR: " << entry.message << std::endl;
        break;
    case LogLevel::Warning:
        std::cerr << "WARNING: " << entry.message << std::endl;
        break;
    case LogLevel::Info:
        std::cout << "INFO: " << entry.message << std::endl;
        break;
    case LogLevel::Debug:
        std::cout << "DEBUG: " << entry.message << std::endl;
        break;
      case LogLevel::Input:
        std::cout << "INPUT: " << entry.message << std::endl;
        break;
    case LogLevel::Clear:
        std::cout << "CLEAR: " << entry.message << std::endl;
        break;
    case LogLevel::Destroy:
        std::cout << "DESTROY: " << entry.message << std::endl;
        break;
    }

    std::ofstream logFile("log.txt", std::ios::app);
    if (logFile.is_open()) {
        logFile << entry.message << std::endl;
        logFile.close();
    }
}

template<typename T>
const std::deque<typename Logger<T>::LogEntry>& Logger<T>::GetLogs() const {
    return logs;
}

template<typename T>
void Logger<T>::Info(const std::string& message, T Num) {
    Log(LogLevel::Info, message, Num);
}

template<typename T>

void Logger<T>::Error(const std::string& message, T Num, const char* file, int line) {
    Log(LogLevel::Error, message, Num, file, line);
}

template<typename T>
void Logger<T>::Warning(const std::string& message, T Num, const char* file, int line) {
    Log(LogLevel::Warning, message, Num, file, line);
}

template<typename T>
void Logger<T>::Debug(const std::string& message, T Num) {
    Log(LogLevel::Debug, message, Num);
}

template<typename T>
void Logger<T>::Input(const std::string& message, T Num) {
    Log(LogLevel::Input, message, Num);
}

template<typename T>
void Logger<T>::Clear(const std::string& message, T Num) {
    Log(LogLevel::Clear, message, Num);
}

template<typename T>
void Logger<T>::Destroy(const std::string& message, T Num) {
    Log(LogLevel::Destroy, message, Num);
}

template class Logger<double>;