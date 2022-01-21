#include "AppLifetimeResources.h"
#include "StaticData/TestStaticDataManager.h"
#include "MatchMaking/TestMatchMaker.h"

bool AppLifetimeResources::loadResources()
{
    m_staticDataManager = std::make_unique<TestStaticDataManager>(200);
    m_matchMaker = std::make_unique<TestMatchMaker>(69, "player0", "player1", 0);
    return true;
}
