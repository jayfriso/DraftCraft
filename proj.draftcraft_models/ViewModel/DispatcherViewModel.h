#pragma once

#include "IListenerView.h"
#include <vector>

template <typename TThisType>
class DispatcherViewModel
{
private:
    std::vector<IListenerView< TThisType>*> m_listeners;
public:
    DispatcherViewModel() {}
    ~DispatcherViewModel() = default;

    void addListener(IListenerView<TThisType>& listener)
    {
        m_listeners.push_back(&listener);
    }

    void clearListeners()
    {
        m_listeners.clear();
    }

    void notifyToUpdate() const
    {
        for (IListenerView<TThisType>* listener : m_listeners)
        {
            listener->update(static_cast<const TThisType*>(this));
        }
    }
};