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
    Vec2 normalizedOffset{ Vec2::ZERO };
    if (offset != Vec2::ZERO)
    {
        Vec2 parentContentSize = node->getParent()->getContentSize();
        normalizedOffset = Vec2{ offset.x / parentContentSize.x, offset.y / parentContentSize.y };
    }
    node->setPositionNormalized(position + normalizedOffset);
}

Sprite* UIUtils::createGenericRoundedRect(Size size, Color3B color)
{
    auto result = Sprite::create("ui/common/rounded_rect.png");
    result->setCenterRectNormalized(Rect(Vec2(0.2, 0.2), Size(0.6, 0.6)));
    result->setContentSize(size);
    result->setColor(color);
    return result;
}

void UIUtils::distributeChildrenHorizontal(Node* node, float space, float yContentSize)
{
    auto children = node->getChildren();
    size_t childCount = node->getChildrenCount();
    float currentX{ 0 };
    float yPos{ yContentSize / 2 };
    for (auto child : children)
    {
        child->setAnchorPoint(Vec2(0, 0.5));
        child->setPosition(currentX, yPos);
        currentX += child->getContentSize().width + space;
    }
    currentX -= space;
    node->setContentSize(Size(currentX, yContentSize));
}