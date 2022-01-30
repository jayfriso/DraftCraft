#pragma once
#include "cocos2d.h"
#include "ViewModel/AbstractListenerView.h"
#include "Model/DraftPile.h"
#include <array>
#include "HorizontalLayoutContainer.h"
#include "VerticalLayoutContainer.h"


USING_NS_CC;

class DraftPileView : public Node, public AbstractListenerView<DraftPile>
{
private:
    static constexpr size_t MAX_CARDS_IN_COLUMN{ 3 };
    static constexpr size_t MAX_COLUMNS{ 2 };

    HorizontalLayoutContainer* m_columnContainer;
    std::array<VerticalLayoutContainer*, MAX_COLUMNS> m_columns;

    void setCards(const vector<const Card*>& cards);

public:
    CREATE_FUNC(DraftPileView);
    virtual void initWithModel(DraftPile& viewModel) override;
    virtual void update(const DraftPile& viewModel) override;
};

