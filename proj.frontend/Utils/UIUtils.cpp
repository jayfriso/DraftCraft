#include "UIUtils.h"

void UIUtils::setAnchoredPosition(Node* node, AnchorPosition anchorPosition, Vec2 offset)
{
    Vec2 position{ 0, 0 };
    switch (anchorPosition)
    {
        case AnchorPosition::BottomLeft:
            position = Vec2{ 0,0 };
            break;
        case AnchorPosition::BottomCenter:
            position = Vec2{ 0.5,0 };
            break;
        case AnchorPosition::BottomRight:
            position = Vec2{ 1,0 };
            break;
        case AnchorPosition::CenterLeft:
            position = Vec2{ 0,0.5 };
            break;
        case AnchorPosition::CenterCenter:
            position = Vec2{ 0.5,0.5 };
            break;
        case AnchorPosition::CenterRight:
            position = Vec2{ 1,0.5 };
            break;
        case AnchorPosition::TopLeft:
            position = Vec2{ 0,1 };
            break;
        case AnchorPosition::TopCenter:
            position = Vec2{ 0.5,1 };
            break;
        case AnchorPosition::TopRight:
            position = Vec2{ 1,1 };
            break;
    }
    node->setAnchorPoint(position);
    node->setPositionNormalized(position);
    if (offset != Vec2::ZERO)
        node->setPosition(node->getPosition() + offset);
}

Sprite* UIUtils::createGenericRoundedRect(Size size, Color3B color)
{
    auto result = Sprite::create("ui/common/rounded_rect.png");
    result->setCenterRectNormalized(Rect(Vec2(0.2, 0.2), Size(0.6, 0.6)));
    result->setContentSize(size);
    result->setColor(color);
    return result;
}

void UIUtils::distributeChildrenHorizontal(Node* node)
{
    auto children = node->getChildren();
    size_t childCount = node->getChildrenCount();
    for (size_t i = 0; i < childCount; i++)
    {
        float positionX = (float)(i + 1) / (childCount + 1);
        children.at(i)->setAnchorPoint(Vec2(0.5, 0.5));
        children.at(i)->setPositionNormalized(Vec2(positionX, 0.5));
    }
}