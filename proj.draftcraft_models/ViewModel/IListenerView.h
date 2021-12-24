#pragma once
#include "DispatcherViewModel.h"

// Forward Declaration
class DispatcherViewModel;

class IListenerView
{
public:
    virtual ~IListenerView() = default;

    virtual void update(const DispatcherViewModel& viewModel) = 0;
};

