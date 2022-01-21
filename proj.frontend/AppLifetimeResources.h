#pragma once

#include <memory>
#include "StaticData/IStaticDataManager.h"
#include "MatchMaking/IMatchMaker.h"

// Class that manages app lifetime resources.
// These are resources that should always exist throughout the lifetime of the app. Thus this class should be held by an object that exists through the apps lifetime (such as AppDelegate).
// All resources are owned by this class, thus should be held through unique ptrs
class AppLifetimeResources
{
private:
    std::unique_ptr<IStaticDataManager> m_staticDataManager;
    std::unique_ptr<IMatchMaker> m_matchMaker;
public:
    const IStaticDataManager& staticDataManager() { return *m_staticDataManager; }
    const IMatchMaker& matchMaker() { return *m_matchMaker; }

    bool loadResources();
};

