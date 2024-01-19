#pragma once
#include <functional>
#include <vector>

namespace cjk {

template <typename EventArgs>
class BroadcastEvent {
    using CbT = std::function<void(const EventArgs&)>;
    std::vector<CbT> m_cbs;

public:
    void AddListener(CbT&& cb) { m_cbs.push_back(cb); }

    void Trigger(const EventArgs& a)
    {
        for (const auto& cb : m_cbs) {
            cb(a);
        }
    }
};

template <>
class BroadcastEvent<void> {
    using CbT = std::function<void(void)>;
    std::vector<CbT> m_cbs;

public:
    void AddListener(CbT&& cb) { m_cbs.push_back(cb); }

    void Trigger()
    {
        for (const auto& cb : m_cbs) {
            cb();
        }
    }
};

template <typename EventArgs>
class SignglecastEvent {
    using CbT = std::function<void(const EventArgs&)>;
    CbT m_cb;

public:
    void SetListener(CbT&& cb) { m_cb = cb; }

    void Trigger(const EventArgs& a)
    {
        if(m_cb)
            m_cb(a);
    };
};

}