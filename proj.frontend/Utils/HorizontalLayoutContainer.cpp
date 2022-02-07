#include "HorizontalLayoutContainer.h"
#include "UIUtils.h"

using namespace std;

float HorizontalLayoutContainer::getYPos() const
{
    return m_childAnchorPoint.y * m_yContentSize;
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
    child->setAnchorPoint(m_childAnchorPoint);
    if (m_ignoreInvisible && !child->isVisible())
    {
        child->setPosition(Vec2{ 0, getYPos() });

        Node::addChild(child);
    }
    else
    {
        float childBoundingWidth = child->getBoundingBox().size.width;
        float xPos{ _contentSize.width + m_space + (m_childAnchorPoint.x * childBoundingWidth) };
        child->setPosition(Vec2{ xPos, getYPos() });
        float additionalContentSize{ childBoundingWidth + m_space };
        setContentSize(_contentSize + Size{ additionalContentSize, 0 });
        Node::addChild(child);
    }
}

void HorizontalLayoutContainer::setChildAnchorPoint(Vec2 anchorPoint)
{
    m_childAnchorPoint = anchorPoint;
    for (auto child : _children)
    {
        child->setAnchorPoint(m_childAnchorPoint);
    }
    redistribute();
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

        float boundingWidth{ child->getBoundingBox().size.width };
        float xPosFromAnchor{ m_childAnchorPoint.x * boundingWidth };

        child->setPositionX(currentX + xPosFromAnchor);
        currentX += boundingWidth + m_space;
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
