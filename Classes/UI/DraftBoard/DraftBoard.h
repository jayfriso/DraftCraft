#pragma once

#include "cocos2d.h"
USING_NS_CC;

class DraftBoard : public Node
{
private:
    static const float WIDTH;

public:
    virtual bool init() override;
    CREATE_FUNC(DraftBoard);
};

