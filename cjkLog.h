#pragma once
#include <stdexcept>

#include "macroUtil.h"
#include "raii.h"

namespace cjk {

enum class LogLevel : char {
    Debug = 'D',
    Info = 'I',
    Error = 'E',
    MachineRead = 'M'
};

class LogTransaction final {
    void* m_implData; // no std::any to avoid overhead for small systems
    raii::DeletedCopy m_noCopy;

public:
    LogTransaction(LogLevel);
    ~LogTransaction();

    LogTransaction& Location(const char* file, size_t lineNum);
    LogTransaction& IgnoredExcpetion(const std::exception&);

    LogTransaction& operator()(const char*);
    LogTransaction& operator()(size_t);
    LogTransaction& operator()(int);
};

inline LogTransaction logDebug() { return LogTransaction(LogLevel::Debug); }
inline LogTransaction logInfo() { return LogTransaction(LogLevel::Info); }
inline LogTransaction logError() { return LogTransaction(LogLevel::Error); }

}

#define CJK_LOG_LOCTION() \
    Location(CJK_STRINGIFY(__FILE__), __LINE__)
