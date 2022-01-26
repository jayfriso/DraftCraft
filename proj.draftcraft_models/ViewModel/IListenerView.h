#pragma once
#include "DispatcherViewModel.h"

template <typename TTypeOfViewModel>
class IListenerView
{
public:
    virtual ~IListenerView() = default;

    virtual void update(const TTypeOfViewModel* viewModel) = 0;
};

