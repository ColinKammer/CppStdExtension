#pragma once
#include <memory>

namespace cjk {

template <typename T>
class RuntimeOwningUniquePtr final {
    T* m_ptr = nullptr;
    bool m_owning = false;

public:
    RuntimeOwningUniquePtr() = default;
    RuntimeOwningUniquePtr(T* ptr)
        : m_ptr(ptr)
    {
    }
    RuntimeOwningUniquePtr(std::unique_ptr<T>&& ptr)
        : m_ptr(ptr.release())
        , m_owning(true)
    {
    }

    RuntimeOwningUniquePtr(const RuntimeOwningUniquePtr&) = delete;
    RuntimeOwningUniquePtr& operator=(const RuntimeOwningUniquePtr&) = delete;

    RuntimeOwningUniquePtr(RuntimeOwningUniquePtr&& o)
        : m_ptr(o.m_ptr)
        , m_owning(o.m_owning)
    {
        o.m_ptr = nullptr;
        // o.m_owning = false; not needed
    }

    RuntimeOwningUniquePtr& operator=(RuntimeOwningUniquePtr&& o)
    {
        if (m_owning)
            delete m_ptr;
        m_ptr = o.m_ptr;
        m_owning = o.m_owning;
        o.m_ptr = nullptr;
        // o.m_owning = false; not needed
        return *this;
    }

    RuntimeOwningUniquePtr& operator=(T* n)
    {
        if (m_owning)
            delete m_ptr;
        m_ptr = n;
        m_owning = false;
        return *this;
    }
    RuntimeOwningUniquePtr& operator=(std::unique_ptr<T>&& n)
    {
        if (m_owning)
            delete m_ptr;
        m_ptr = n.release();
        m_owning = true;
        return *this;
    }

    T* operator->() const noexcept { return m_ptr; }

    operator bool() const noexcept { return m_ptr != nullptr; }

    T* release() noexcept
    {
        m_owning = false;
        return m_ptr;
    }
    T* get() const noexcept { return m_ptr; }
};

}