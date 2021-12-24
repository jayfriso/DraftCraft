#pragma once

#include "IListenerView.h"

// Forward declaration
class IListenerView;

// Class used to subscribe a view to the model, in order to be able to send notifications for the view to update
class DispatcherViewModel
{
private:
    IListenerView* m_listener;
public:
    DispatcherViewModel() : m_listener{ nullptr } {}
    ~DispatcherViewModel();

    void subscribeListener(IListenerView* listener) { m_listener = listener; }
    void unsubscribeListener() { m_listener = nullptr; }
    bool isSubscribed() const { return m_listener != nullptr; }
    void notifyToUpdate() const;
};

