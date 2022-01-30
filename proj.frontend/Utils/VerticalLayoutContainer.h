#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "CustomMacros.h"

USING_NS_CC;
using namespace ui;

enum class VerticalAnchorType
{
    Left,
    Center,
    Right
};
class VerticalLayoutContainer : public Node
{
private:
    float m_space;
    float m_xContentSize;
    bool m_ignoreInvisible;
    VerticalAnchorType m_anchorType;

    float getXPos() const;
    float getXAnchor() const;
public:
    VerticalLayoutContainer(float space, float xContentSize) : m_space{ space }, m_xContentSize{ xContentSize }, m_ignoreInvisible{ true }, m_anchorType{ VerticalAnchorType::Center } {};
    CREATE_FUNC_TWO_PARAM(VerticalLayoutContainer, float, float);

    virtual bool init() override;
    virtual void addChild(Node* child) override;
    void setAnchorType(VerticalAnchorType anchorType);
    void redistribute();
    void setSpace(float space) { m_space = space; }
};

