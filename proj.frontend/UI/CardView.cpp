#include "CardView.h"
#include "UIUtils.h"
#include "UIConstants.h"

const Size CardView::DEFAULT_SIZE{ 582, 800 };

bool CardView::init()
{
    if (!EventNode::init())
        return false;

    setContentSize(DEFAULT_SIZE);
    m_frontContainer = Node::create();
    m_frontContainer->setContentSize(DEFAULT_SIZE);
    addChild(m_frontContainer);
    ui_utils::setAnchoredPosition(m_frontContainer, AnchorPosition::CenterCenter);
    
    auto bg = Sprite::create("ui/card/card_bg.png");
    m_frontContainer->addChild(bg, 0);
    bg->setCenterRectNormalized(Rect(Vec2(0.25f, 0.25f), Size(0.5f, 0.5f)));
    bg->setContentSize(DEFAULT_SIZE);
    ui_utils::setAnchoredPosition(bg, AnchorPosition::CenterCenter);

    auto manaBg = Sprite::create("ui/card/mana_icon.png");
    m_frontContainer->addChild(manaBg, 2);
    ui_utils::setAnchoredPosition(manaBg, AnchorPosition::TopLeft, Vec2{ 10,-10 });
    m_manaValueLabel = Label::createWithTTF("0", UIConstants::FONT_FREDOKA_ONE_REGULAR, 100);
    m_manaValueLabel->setTextColor(Color4B{ UIConstants::COLOR_DARK_BLUE });
    manaBg->addChild(m_manaValueLabel, 2);
    ui_utils::setAnchoredPosition(m_manaValueLabel, AnchorPosition::CenterCenter);

    m_attackValueContainer = Sprite::create("ui/card/attack_icon.png");
    m_frontContainer->addChild(m_attackValueContainer, 2);
    ui_utils::setAnchoredPosition(m_attackValueContainer, AnchorPosition::BottomLeft, Vec2{ 10,10 });
    m_attackValueLabel = Label::createWithTTF("1", UIConstants::FONT_FREDOKA_ONE_REGULAR, 72);
    m_attackValueLabel->setTextColor(Color4B{ UIConstants::COLOR_DARK_BLUE });
    m_attackValueContainer->addChild(m_attackValueLabel);
    m_attackValueLabel->setPositionNormalized(Vec2{ 0.575, 0.375});

    m_defenseValueContainer = Sprite::create("ui/card/defense_icon.png");
    m_frontContainer->addChild(m_defenseValueContainer, 2);
    ui_utils::setAnchoredPosition(m_defenseValueContainer, AnchorPosition::BottomRight, Vec2{ -10,10 });
    m_defenseValueLabel = Label::createWithTTF("1", UIConstants::FONT_FREDOKA_ONE_REGULAR, 72);
    m_defenseValueLabel->setTextColor(Color4B{ UIConstants::COLOR_DARK_BLUE });
    m_defenseValueContainer->addChild(m_defenseValueLabel);
    m_defenseValueLabel->setPositionNormalized(Vec2{ 0.5, 0.55 });

    m_cardArtSprite = Sprite::create("ui/card/placeholder_creature_art.png");
    m_frontContainer->addChild(m_cardArtSprite, 1);
    ui_utils::setAnchoredPosition(m_cardArtSprite, AnchorPosition::TopCenter, Vec2{ 0,-50 });
    m_cardArtSprite->setContentSize(Size{ 490, 333 });

    auto cardTextBg = ui_utils::createGenericRoundedRect(Size{ 490, 355 }, Color3B::WHITE);
    m_frontContainer->addChild(cardTextBg, 1);
    ui_utils::setAnchoredPosition(cardTextBg, AnchorPosition::BottomCenter, Vec2{ 0, 50 });;
    string defaultString = "This creature gets +1/+1 for each Sponge you control."; 
    m_cardTextLabel = Label::createWithTTF(defaultString, UIConstants::FONT_LATO_SEMI_BOLD, 30, Size{465, 235});
    m_cardTextLabel->setTextColor(Color4B::BLACK);
    m_cardTextLabel->enableWrap(true);
    cardTextBg->addChild(m_cardTextLabel);
    ui_utils::setAnchoredPosition(m_cardTextLabel, AnchorPosition::TopCenter, Vec2{ 0, -50 });;

    auto nameBg = Sprite::create("ui/card/card_name_bg.png");
    m_frontContainer->addChild(nameBg, 2);
    ui_utils::setAnchoredPosition(nameBg, AnchorPosition::TopCenter, Vec2{ 0, -340 });;
    m_nameContainer = HorizontalLayoutContainer::create(10, nameBg->getContentSize().height - 5);
    nameBg->addChild(m_nameContainer);
    m_cardTypeSprite = Sprite::create("ui/card/creature_icon.png");
    m_nameContainer->addChild(m_cardTypeSprite);
    string name = m_cardData != nullptr ? m_cardData->displayName() : "";
    m_nameLabel = Label::createWithTTF(name, UIConstants::FONT_FREDOKA_ONE_REGULAR, 35);
    m_nameLabel->setTextColor(Color4B{ UIConstants::COLOR_DARK_BLUE });
    m_nameContainer->addChild(m_nameLabel);
    ui_utils::setAnchoredPosition(m_nameContainer, AnchorPosition::CenterCenter);;

    m_backSprite = Sprite::create("ui/card/card_back.png");
    addChild(m_backSprite, 0);
    ui_utils::setAnchoredPosition(m_backSprite, AnchorPosition::CenterCenter);;
    m_backSprite->setVisible(false);

    return true;
}

void CardView::setCardData(const Card* cardData)
{
    m_cardData = cardData;
    if (m_cardData != nullptr)
    {
        m_nameLabel->setString(cardData->displayName());
        m_nameContainer->redistribute();
        ui_utils::setAnchoredPosition(m_nameContainer, AnchorPosition::CenterCenter);;
    }
}

void CardView::resize(float targetHeight)
{
    setScale(targetHeight / DEFAULT_SIZE.height);
}

void CardView::flip(bool isFront)
{
    if (isFront == m_isFront)
        return;
    m_isFront = isFront;
    m_frontContainer->setVisible(isFront);
    m_backSprite->setVisible(!isFront);
}
