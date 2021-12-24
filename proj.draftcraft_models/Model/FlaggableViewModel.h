#pragma once

#include "IViewModel.h"

// Base class for models that can be flagged to inform the view that the view is dirty
// Should be flagged anytime the model changes
class FlaggableViewModel : public IViewModel
{
protected:
    bool m_isViewDirty;
    void flagViewDirty() { m_isViewDirty = true; }
public :
    FlaggableViewModel() : m_isViewDirty{ false } {}
    virtual bool isViewDirty() const override { return m_isViewDirty; }
    virtual void clearViewDirty() override { m_isViewDirty = false; }
};

