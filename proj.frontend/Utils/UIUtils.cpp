#include "UIUtils.h"
#include <numeric>
#include "UIConstants.h"

namespace ui_utils
{
    void setAnchoredPosition(Node* node, AnchorPosition anchorPosition, Vec2 offset, tuple<bool, Vec2> overrideAnchorPoint)
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
        if (get<0>(overrideAnchorPoint))
            node->setAnchorPoint(get<1>(overrideAnchorPoint));
        else
            node->setAnchorPoint(position);
        Vec2 normalizedOffset{ Vec2::ZERO };
        if (offset != Vec2::ZERO)
        {
            Vec2 parentContentSize = node->getParent()->getContentSize();
            normalizedOffset = Vec2{ offset.x / parentContentSize.x, offset.y / parentContentSize.y };
        }
        node->setPositionNormalized(position + normalizedOffset);
    }

    Sprite* createGenericRoundedRect(const Size& size, const Color3B& color)
    {
        auto result = Sprite::create("ui/common/rounded_rect.png");
        result->setCenterRectNormalized(Rect{ Vec2{0.2, 0.2}, Size{0.6, 0.6} });
        result->setContentSize(size);
        result->setColor(color);
        return result;
    }

    Sprite* createGenericRoundedRectOutline(const Size& sizeOfRoundedRect, const Color3B& color)
    {
        auto result = Sprite::create("ui/common/rounded_rect_outline.png");
        result->setCenterRectNormalized(Rect{ Vec2{0.2, 0.2}, Size{0.6, 0.6} });
        result->setContentSize(Size{ sizeOfRoundedRect.width + 24, sizeOfRoundedRect.height + 24 });
        result->setColor(color);
        return result;
    }

    EventSprite* createGenericOrangeButton(const Size& size, const string& labelText, float fontSize)
    {
        auto result = EventSprite::create("ui/common/orange_button.png", "ui/common/orange_button_pressed.png");
        if (!result)
            return nullptr;
        result->setCenterRectNormalized(Rect{ Vec2{0.2, 0.3}, Size{0.6, 0.5} });
        result->setContentSize(size);

        if (!labelText.empty())
        {
            auto label = Label::createWithTTF(labelText, UIConstants::FONT_FREDOKA_ONE_REGULAR, fontSize);
            result->addChild(label);
            setAnchoredPosition(label, AnchorPosition::CenterCenter);
            label->setColor(UIConstants::COLOR_DARK_BLUE);
        }

        return result;
    }

    void distributeChildrenHorizontal(Node* node, float space, float yContentSize, bool ignoreInvisible)
    {
        auto children = node->getChildren();
        size_t childCount = node->getChildrenCount();
        float currentX{ 0 };
        float yPos{ yContentSize / 2 };
        for (auto child : children)
        {
            if (ignoreInvisible && !child->isVisible())
                continue;

            child->setAnchorPoint(Vec2(0, 0.5));
            child->setPosition(currentX, yPos);
            currentX += child->getContentSize().width + space;
        }
        currentX -= space;
        node->setContentSize(Size(currentX, yContentSize));
    }

    void distributeChildrenVertical(Node* node, float space, float xContentSize, bool ignoreInvisible)
    {
        auto children = node->getChildren();
        size_t childCount = node->getChildrenCount();
        float currentY{ 0 };
        float xPos{ xContentSize / 2 };
        // First loop to get total height, as we are going from top
        float totalHeight{ 0 };
        for (auto child : children)
        {
            if (ignoreInvisible && !child->isVisible())
                continue;
            totalHeight += child->getBoundingBox().size.height;
            totalHeight += space;
        }
        totalHeight -= space; // Subtract the last space
        node->setContentSize(Size(xContentSize, totalHeight));

        for (auto child : children)
        {
            if (ignoreInvisible && !child->isVisible())
                continue;
            child->setAnchorPoint(Vec2(0.5, 1));
            child->setPosition(xPos, totalHeight - currentY);
            currentY += child->getBoundingBox().size.height + space;
        }
    }
}