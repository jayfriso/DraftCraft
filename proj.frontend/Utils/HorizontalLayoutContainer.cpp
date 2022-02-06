#include "HorizontalLayoutContainer.h"
#include "UIUtils.h"

using namespace std;

float HorizontalLayoutContainer::getYPos() const
{
    return getYAnchor() * m_yContentSize;
}

float HorizontalLayoutContainer::getYAnchor() const
{
    switch (m_anchorType)
    {
        case HorizontalAnchorType::Top:
            return 1.0f;
        case HorizontalAnchorType::Center:
            return 0.5f;
        case HorizontalAnchorType::Bottom:
            return 0.0f;
    }
}

bool HorizontalLayoutContainer::init()
{
    if (!Node::init())
        return false;
    setContentSize(Size{ 0, m_yContentSize });
    return true;
}

void HorizontalLayoutContainer::addChild(Node* child)
{
    child->setAnchorPoint(Vec2{ 0, getYAnchor() });
    if (m_ignoreInvisible && !child->isVisible())
    {
        child->setPosition(Vec2{ 0, getYPos() });

        Node::addChild(child);
    }
    else
    {
        float xPos{ _contentSize.width + m_space };
        child->setPosition(Vec2{ xPos, getYPos() });
        float additionalContentSize{ child->getBoundingBox().size.width + m_space };
        setContentSize(_contentSize + Size{ additionalContentSize, 0 });
        Node::addChild(child);
    }
}

void HorizontalLayoutContainer::setAnchorType(HorizontalAnchorType anchorType)
{
    m_anchorType = anchorType;
    for (auto child : _children)
    {
        child->setAnchorPoint(Vec2{ 0.0f, getYAnchor() });
        child->setPositionY(getYPos());
    }
}

void HorizontalLayoutContainer::redistribute()
{
    size_t childCount = _children.size();
    if (childCount == 0)
        return;
    float currentX{ 0 };
    for (auto child : _children)
    {
        if (m_ignoreInvisible && !child->isVisible())
            continue;

        child->setPositionX(currentX);
        currentX += child->getBoundingBox().size.width + m_space;
    }
    currentX -= m_space;
    setContentSize(Size{ currentX, m_yContentSize });
}

void HorizontalLayoutContainer::setSpace(float space, bool shouldRedistribute)
{
    m_space = space;
    if (shouldRedistribute)
        redistribute();
}
