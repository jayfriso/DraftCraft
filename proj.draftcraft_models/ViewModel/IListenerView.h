#pragma once

template <typename TTypeOfViewModel>
class IListenerView
{
private:
    // Private due to the fact that the view should not have direct reference to model
    // We only have a reference here in order to be able to detach from the model on destruction
    TTypeOfViewModel* m_viewModel;

public:
    virtual ~IListenerView()
    {
        detachFromModel();
    }

    virtual void update(const TTypeOfViewModel& viewModel) = 0;

    virtual void initWithModel(TTypeOfViewModel& model)
    {
        m_viewModel = &model;
        m_viewModel->addListener(*this);
    }
    virtual void detachFromModel()
    {
        if (m_viewModel != nullptr)
            m_viewModel->removeListener(*this);
    }
};

