#pragma once
#include "cocos2d.h"

USING_NS_CC;

enum class AnchorPosition
{
    BottomLeft,
    BottomCenter,
    BottomRight,
    CenterLeft,
    CenterCenter,
    CenterRight,
    TopLeft,
    TopCenter,
    TopRight
};

class UIUtils
{
public:
    static void setAnchoredPosition(Node* node, AnchorPosition anchorPosition, Vec2 offset = Vec2::ZERO);

    static Sprite* createGenericRoundedRect(Size size, Color3B color);

    static void distributeChildrenHorizontal(Node* node, float space, float yContantSize);
};

