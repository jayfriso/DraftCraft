#pragma once
#include <string>

using namespace std;

class Card
{
private:
    string m_Id;
    string m_DisplayName;
public:
    Card(string id, string displayName);

    string id() const { return m_Id; }
    string displayName() const { return m_DisplayName; }
};

