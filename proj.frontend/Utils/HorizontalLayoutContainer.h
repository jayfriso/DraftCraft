#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "CustomMacros.h"

USING_NS_CC;
using namespace ui;

enum class HorizontalAnchorType
{
    Top,
    Center,
    Bottom
};

class HorizontalLayoutContainer : public Node
{
private:
    float m_space;
    float m_yContentSize;
    bool m_ignoreInvisible;
    HorizontalAnchorType m_anchorType;

    float getYPos() const;
    float getYAnchor() const;

public:
    HorizontalLayoutContainer(float space, float yContentSize) : m_space{ space }, m_yContentSize{ yContentSize }, m_ignoreInvisible{ true }, m_anchorType{ HorizontalAnchorType::Center }{};
    CREATE_FUNC_TWO_PARAM(HorizontalLayoutContainer, float, float);

    virtual bool init() override;
    virtual void addChild(Node* child) override;
    void setAnchorType(HorizontalAnchorType anchorType);
    void redistribute();
    void setSpace(float space);
};

