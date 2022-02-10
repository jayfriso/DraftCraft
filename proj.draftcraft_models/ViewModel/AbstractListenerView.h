#pragma once

template <typename TTypeOfViewModel>
class AbstractListenerView
{
private:
    // Private due to the fact that the view should not have a non const reference to model
    // We only have a reference here in order to be able to detach from the model on destruction
    // If viewmodel needs the model, should get it through getViewModel()
    TTypeOfViewModel* m_viewModel;

protected:
    const TTypeOfViewModel* const getViewModel() { return m_viewModel; }

public:
    virtual ~AbstractListenerView()
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

