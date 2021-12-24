#include "pch.h"
#include "CppUnitTest.h"
#include "../proj.draftcraft_models/Model/DraftDeck.h";
#include "../proj.draftcraft_models/StaticData/TestStaticDataManager.h"
#include "../proj.draftcraft_models/Model/DraftPile.h";

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Test
{
	TEST_CLASS(ModelTests)
	{
	public:

		TEST_METHOD(testDraftDeck)
		{
			GameConfig gameConfig{ 100, 40 };
			TestStaticDataManager staticDataManager{ 200, gameConfig };
			DraftDeck draftDeck{ staticDataManager, 69 };
			
			vector<string> expectedValues{ "test_187", "test_0", "test_129" };
			const Card* cardPointer{ nullptr };
			unsigned int expectedCardsLeft = 100;
			Assert::AreEqual(expectedCardsLeft, draftDeck.cardsLeft());

			for (auto expectedValue : expectedValues)
			{
				cardPointer = draftDeck.drawCard();
				Assert::AreEqual(expectedValue, cardPointer->id());
				expectedCardsLeft--;
				Assert::AreEqual(expectedCardsLeft, draftDeck.cardsLeft());
			}
		}

		TEST_METHOD(testDraftPile)
		{
			GameConfig gameConfig{ 100, 40 };
			TestStaticDataManager staticDataManager{ 200, gameConfig };
			DraftDeck draftDeck{ staticDataManager, 69 };
			DraftPile draftPile{ draftDeck };

			// Draft pile should start with 1 pile
			Assert::AreEqual((size_t)1, draftPile.cardsInPile().size());

			const Card* draftedCard{ nullptr };

			// Add 1 extra card then draft the 2nd card
			draftPile.addCardToPile();
			draftedCard = draftPile.draftCardAtIndex(1);
			Assert::AreEqual(string("test_0"), draftedCard->id());

			// Add an extra card, the draft the first card in pile
			draftPile.addCardToPile();
			Assert::AreEqual((size_t)2, draftPile.cardsInPile().size());
			draftedCard = draftPile.draftCardAtIndex(0);
			Assert::AreEqual(string("test_129"), draftedCard->id());
		}
	};
}
