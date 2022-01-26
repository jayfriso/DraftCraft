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

    void addListener(IListenerView<TThisType>& listener);
    void clearListeners();
    void notifyToUpdate() const;
};