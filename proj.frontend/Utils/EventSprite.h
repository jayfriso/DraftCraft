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
    string m_spritePath;
    Sprite* m_sprite;
public:
    EventSprite(string spritePath) : 
        m_spritePath{ spritePath },
        EventNode{ true } {}
    CREATE_FUNC_ONE_PARAM(EventSprite, string);
    
    virtual bool init() override;
    virtual void setContentSize(const Size& size) override;

    Sprite* sprite() { return m_sprite; }
};