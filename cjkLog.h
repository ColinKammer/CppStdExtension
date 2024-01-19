#pragma once
#include <stdexcept>

#include "macroUtil.h"
#include "raii.h"

namespace cjk {
class LogTransaction final {
    void* m_implData; // no std::any to avoid overhead for small systems
    raii::DeletedCopy m_noCopy;

public:
    LogTransaction();
    ~LogTransaction();

    LogTransaction& Location(const char* file, size_t lineNum);
    LogTransaction& IgnoredExcpetion(const std::exception&);

    LogTransaction& operator()(const char*);
    LogTransaction& operator()(size_t);
    LogTransaction& operator()(int);
};

[[nodiscard]] inline LogTransaction log() { return LogTransaction(); }

}

#define CJK_LOG_LOCTION() \
    Location(CJK_STRINGIFY(__FILE__), __LINE__)
