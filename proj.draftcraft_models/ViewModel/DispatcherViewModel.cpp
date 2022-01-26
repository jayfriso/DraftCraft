#include "DispatcherViewModel.h"

template<typename TThisType>
void DispatcherViewModel<TThisType>::addListener(IListenerView<TThisType>& listener)
{
    m_listeners.push_back(&listener);
}

template<typename TThisType>
void DispatcherViewModel<TThisType>::clearListeners()
{
    m_listeners.clear();
}

template<typename TThisType>
void DispatcherViewModel<TThisType>::notifyToUpdate() const
{
    for (auto listener : m_listeners)
    {
        listener.update(static_cast<const TThisType *>(this));
    }
}
