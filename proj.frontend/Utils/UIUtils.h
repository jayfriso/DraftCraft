#pragma once
#include "cocos2d.h"
#include <tuple>
#include <string>
#include "ui/CocosGUI.h"
#include "EventSprite.h"

USING_NS_CC;
using namespace std;
using namespace ui;

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

namespace ui_utils
{
    void setAnchoredPosition(Node* node, AnchorPosition anchorPosition, Vec2 offset = Vec2::ZERO, tuple<bool, Vec2> overrideAnchorPoint = tuple<bool, Vec2>(false, Vec2::ZERO));

    Sprite* createGenericRoundedRect(const Size& size, const Color3B& color);
    Sprite* createGenericRoundedRectOutline(const Size& sizeOfRoundedRect, const Color3B& color);
    EventSprite* createGenericOrangeButton(const Size& size, const string& labelText = "", float fontSize = 32);

    void distributeChildrenHorizontal(Node* node, float space, float yContantSize, bool ignoreInvisible = true);
    void distributeChildrenVertical(Node* node, float space, float xContentSize, bool ignoreInvisible = true);
};

