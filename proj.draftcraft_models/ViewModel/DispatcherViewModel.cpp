#include "DispatcherViewModel.h"

DispatcherViewModel::~DispatcherViewModel()
{
    unsubscribeListener();
}

void DispatcherViewModel::notifyToUpdate() const
{
    if (isSubscribed())
        m_listener->update(*this);
}
