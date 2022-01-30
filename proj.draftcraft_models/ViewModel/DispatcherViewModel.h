#pragma once

#include "AbstractListenerView.h"
#include <forward_list>

template <typename TThisType>
class DispatcherViewModel
{
private:
    std::forward_list<AbstractListenerView< TThisType>*> m_listeners;
public:
    DispatcherViewModel() {}
    ~DispatcherViewModel() = default;

    void addListener(AbstractListenerView<TThisType>& listener)
    {
        m_listeners.push_front(&listener);
    }

    void removeListener(AbstractListenerView<TThisType>& listener)
    {
        m_listeners.remove(&listener);
    }

    void clearListeners()
    {
        m_listeners.clear();
    }

    void notifyToUpdate() const
    {
        for (AbstractListenerView<TThisType>* listener : m_listeners)
        {
            if (listener != nullptr)
                listener->update(static_cast<const TThisType&>(*this));
        }
    }
};