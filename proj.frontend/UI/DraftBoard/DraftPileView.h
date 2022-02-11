#pragma once
#include "cocos2d.h"
#include "ViewModel/AbstractListenerView.h"
#include "Model/DraftPile.h"
#include <array>
#include "HorizontalLayoutContainer.h"
#include "VerticalLayoutContainer.h"
#include "../CardView.h"

USING_NS_CC;

class DraftPileView : public Node, public AbstractListenerView<DraftPile>
{
private:
    static constexpr size_t MAX_CARDS_IN_COLUMN{ 3 };
    static constexpr size_t MAX_COLUMNS{ 2 };
    static constexpr size_t MAX_CARDS_SHOWN{ MAX_CARDS_IN_COLUMN * MAX_COLUMNS };

    std::vector<Node*> m_nodesToShowWhenSelected;
    HorizontalLayoutContainer* m_columnContainer;
    std::array<VerticalLayoutContainer*, MAX_COLUMNS> m_columns;
    std::array<CardView*, MAX_CARDS_SHOWN> m_cardViews;
    Node* m_overMaxViewContainer;
    Label* m_overMaxLabel;

    void setCards(const vector<const Card*>& cards);

public:
    CREATE_FUNC(DraftPileView);
    virtual void initWithModel(DraftPile& viewModel) override;
    virtual void update(const DraftPile& viewModel) override;

    void toggleSelected(bool isSelected);
    void toggleFlipped(bool isFlipped);
};

