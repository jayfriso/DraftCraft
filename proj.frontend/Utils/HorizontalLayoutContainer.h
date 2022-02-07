#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "CustomMacros.h"

USING_NS_CC;
using namespace ui;

class HorizontalLayoutContainer : public Node
{
private:
    float m_space;
    float m_yContentSize;
    bool m_ignoreInvisible;
    Vec2 m_childAnchorPoint;

    inline float getYPos() const;

public:
    HorizontalLayoutContainer(float space, float yContentSize) : 
        m_space{ space }, 
        m_yContentSize{ yContentSize }, 
        m_ignoreInvisible{ true }, 
        m_childAnchorPoint{ 0, 0.5 }{};
    CREATE_FUNC_TWO_PARAM(HorizontalLayoutContainer, float, float);

    virtual bool init() override;
    virtual void addChild(Node* child) override;
    void setChildAnchorPoint(Vec2 anchorPoint);
    void redistribute();
    void setSpace(float space, bool shouldRedistribute = true);
};

