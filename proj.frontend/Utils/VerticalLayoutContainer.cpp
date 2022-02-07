#include "VerticalLayoutContainer.h"

float VerticalLayoutContainer::getXPos() const
{
    return getXAnchor() * m_xContentSize;
}

float VerticalLayoutContainer::getXAnchor() const
{
    switch (m_anchorType)
    {
        case VerticalAnchorType::Left:
            return 0.0f;
        case VerticalAnchorType::Center:
            return 0.5f;
        case VerticalAnchorType::Right:
            return 1.0f;
    }
}

bool VerticalLayoutContainer::init()
{
    if (!Node::init())
        return false;
    setContentSize(Size{ m_xContentSize, 0 });
    return true;
}

void VerticalLayoutContainer::addChild(Node* child)
{
    child->setAnchorPoint(Vec2{ getXAnchor(), 1 });
    child->setPosition(Vec2{ getXPos(), 0 }); // Put child to bottom

    if (m_ignoreInvisible && !child->isVisible())
    {
        Node::addChild(child);
    }
    else
    {
        // Move other elements up
        float additionalContentSize{ child->getBoundingBox().size.width + m_space };
        for (auto currentChild : _children)
        {
            currentChild->setPositionY(currentChild->getPositionY() + additionalContentSize);
        }
        setContentSize(_contentSize + Size{ additionalContentSize, 0 });
        Node::addChild(child);
    }
}

void VerticalLayoutContainer::setAnchorType(VerticalAnchorType anchorType)
{
    m_anchorType = anchorType;
    for (auto child : _children)
    {
        child->setAnchorPoint(Vec2{ getXAnchor(), 1 });
        child->setPositionY(getXPos());
    }
}

void VerticalLayoutContainer::redistribute()
{
    size_t childCount = _children.size();
    if (childCount == 0)
        return;
    float currentY{ 0 };
    float xPos{ m_xContentSize / 2 };
    // First loop to get total height, as we are going from top
    float totalHeight{ 0 };
    for (auto child : _children)
    {
        if (m_ignoreInvisible && !child->isVisible())
            continue;
        totalHeight += (child->getBoundingBox().size.height + m_space);
    }
    totalHeight -= m_space; // Subtract the last space
    setContentSize(Size(m_xContentSize, totalHeight));
    // Second loop to position children from top
    for (auto child : _children)
    {
        if (m_ignoreInvisible && !child->isVisible())
            continue;
        child->setPositionY(totalHeight - currentY);
        currentY += child->getBoundingBox().size.height + m_space;
    }
}
