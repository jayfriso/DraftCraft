#pragma once

#include "cocos2d.h"
#include "StaticData/Card.h"
#include "CustomMacros.h"
#include "HorizontalLayoutContainer.h"

USING_NS_CC;

class CardView : public Node
{
private:
    static const Size DEFAULT_SIZE;

    const Card* m_cardData;

    Sprite* m_backSprite;
    Node* m_frontContainer;
    Label* m_manaValueLabel;
    Sprite* m_attackValueContainer;
    Label* m_attackValueLabel;
    Sprite* m_defenseValueContainer;
    Label* m_defenseValueLabel;
    HorizontalLayoutContainer* m_nameContainer;
    Label* m_nameLabel;
    Sprite* m_cardTypeSprite;
    Sprite* m_cardArtSprite;
    Label* m_cardTextLabel;

    bool m_isFront;
public:
    CardView(const Card* cardData) :  m_cardData{cardData}, m_isFront{true} {}
    CREATE_FUNC_ONE_PARAM(CardView, const Card*);
    virtual bool init() override;
    void setCardData(const Card* cardData);
    void resize(float targetHeight); 
    void flip(bool isFront);
    bool isFront() const { return m_isFront; }
};

