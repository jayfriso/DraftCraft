#pragma once
class IViewModel
{
public:
    virtual bool isViewDirty() const = 0;
    virtual void clearViewDirty() = 0;
};

