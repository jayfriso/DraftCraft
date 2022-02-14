#pragma once
#include <string>
#include "EventNode.h"
#include "cocos2d.h"
#include "CustomMacros.h"

USING_NS_CC;
using namespace std;

class EventSprite : public EventNode
{
private:
    string m_defaultSpritePath;
    string m_downSpritePath;
    Sprite* m_defaultSprite;
    Sprite* m_downSprite;
public:
    EventSprite(const string& spritePath, const string& downSpritePath) : 
        m_defaultSpritePath{ spritePath },
        m_downSpritePath{ downSpritePath },
        EventNode{ true } {}
    CREATE_FUNC_TWO_PARAM(EventSprite, string, string);
    
    virtual bool init() override;
    virtual void setContentSize(const Size& size) override;
    void setCenterRectNormalized(const cocos2d::Rect& rect);

    Sprite* sprite() { return m_defaultSprite; }

    virtual void handleMouseDown(Event* event) override;
    virtual void handleMouseUp(Event* event) override;
};