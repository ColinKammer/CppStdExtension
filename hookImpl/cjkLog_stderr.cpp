#include "cjkLog.h"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>

namespace cjk {

struct ImplData {
    LogLevel logLevel;
    std::string srcLocation;
    std::string message;
};

LogTransaction::LogTransaction(LogLevel l)
    : m_implData(new ImplData())
{
    auto* cst = static_cast<ImplData*>(m_implData);
    cst->logLevel = l;
}

LogTransaction::~LogTransaction()
{
    auto* cst = static_cast<ImplData*>(m_implData);
    auto now = std::chrono::steady_clock::now();
    auto epochMs = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    std::cerr << static_cast<char>(cst->logLevel) << " ";
    std::cerr << std::setfill('0') << std::setw(6) << (epochMs % 1'000'000);
    std::cerr << cst->srcLocation << " #@";
    std::cerr << cst->message << std::endl;
    delete cst;
}

LogTransaction& LogTransaction::Location(const char* file, size_t lineNum)
{
    static constexpr auto MaxSourceLen = 20;
    auto* cst = static_cast<ImplData*>(m_implData);
    std::string s = file;
    s += ":";
    s += std::to_string(lineNum);
    if (s.size() > MaxSourceLen) {
        s = s.substr(s.size() - MaxSourceLen);
    }
    cst->srcLocation = s;
    return *this;
}

LogTransaction& LogTransaction::operator()(const char* s)
{
    auto* cst = static_cast<ImplData*>(m_implData);
    cst->message = cst->message + " " + s;
    return *this;
}

LogTransaction& LogTransaction::IgnoredExcpetion(const std::exception& e)
{
    operator()("Ignored Exception:");
    operator()(e.what());
    return *this;
}

LogTransaction& LogTransaction::operator()(size_t i)
{
    auto s = std::to_string(i);
    operator()(s.c_str());
    return *this;
}
LogTransaction& LogTransaction::operator()(int i)
{
    auto s = std::to_string(i);
    operator()(s.c_str());
    return *this;
}

}