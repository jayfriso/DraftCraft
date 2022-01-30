#pragma once
#include "cocos2d.h"
#include <tuple>

USING_NS_CC;
using namespace std;

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
    static void setAnchoredPosition(Node* node, AnchorPosition anchorPosition, Vec2 offset = Vec2::ZERO, tuple<bool, Vec2> overrideAnchorPoint = tuple<bool, Vec2>(false, Vec2::ZERO));

    static Sprite* createGenericRoundedRect(Size size, Color3B color);

    static void distributeChildrenHorizontal(Node* node, float space, float yContantSize, bool ignoreInvisible = true);
    static void distributeChildrenVertical(Node* node, float space, float xContentSize, bool ignoreInvisible = true);

};

