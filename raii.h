#pragma once
#include <functional>

namespace cjk::raii {

struct DeletedCopy final {
    DeletedCopy() = default;

    DeletedCopy(const DeletedCopy&) = delete;
    DeletedCopy& operator=(const DeletedCopy&) = delete;

    DeletedCopy(DeletedCopy&&) = default;
    DeletedCopy& operator=(DeletedCopy&&) = default;
};

struct DeletedCopyAndMove final {
    DeletedCopyAndMove() = default;

    DeletedCopyAndMove(const DeletedCopyAndMove&) = delete;
    DeletedCopyAndMove& operator=(const DeletedCopyAndMove&) = delete;

    DeletedCopyAndMove(DeletedCopyAndMove&&) = delete;
    DeletedCopyAndMove& operator=(DeletedCopyAndMove&&) = delete;
};

template <typename FuncT>
struct Lifetime final {
    FuncT m_func;
    bool m_armed;

    Lifetime()
        : m_func()
        , m_armed(false)
    {
    }

    explicit Lifetime(FuncT&& func)
        : m_func(std::move(func))
        , m_armed(true)
    {
    }

    ~Lifetime()
    {
        if (m_armed)
            m_func();
    }

    Lifetime(const Lifetime&) = delete;
    Lifetime& operator=(const Lifetime&) = delete;

    Lifetime(Lifetime&& other) noexcept
        : m_func(std::move(other.m_func))
        , m_armed(true)
    {
        other.m_armed = false;
    }
    Lifetime& operator=(Lifetime&& other) noexcept
    {
        if (m_armed)
            m_func();
        m_func = std::move(other.m_func);
        m_armed = std::move(other.m_armed);
        other.m_armed = false;
        return *this;
    }

    void Disarm() noexcept{
        m_armed = false;
    }
};

using TypeEreasedLifetime = Lifetime<std::function<void(void)>>;

}
