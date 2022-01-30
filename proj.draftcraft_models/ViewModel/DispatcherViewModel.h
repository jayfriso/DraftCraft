#pragma once

#include "IListenerView.h"
#include <forward_list>

template <typename TThisType>
class DispatcherViewModel
{
private:
    std::forward_list<IListenerView< TThisType>*> m_listeners;
public:
    DispatcherViewModel() {}
    ~DispatcherViewModel() = default;

    void addListener(IListenerView<TThisType>& listener)
    {
        m_listeners.push_front(&listener);
    }

    void removeListener(IListenerView<TThisType>& listener)
    {
        m_listeners.remove(&listener);
    }

    void clearListeners()
    {
        m_listeners.clear();
    }

    void notifyToUpdate() const
    {
        for (IListenerView<TThisType>* listener : m_listeners)
        {
            if (listener != nullptr)
                listener->update(static_cast<const TThisType&>(*this));
        }
    }
};