#include "pch.h"
#include "CppUnitTest.h"
#include "StaticData/TestStaticDataManager.h"
#include "Model/GameState.h"
#include "CommandSystem/AbstractCommandProcessor.h"
#include "CommandSystem/Commands/Commands.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

// With a seed of 69 the deck should have cards with the following indices
// 187, 0, 129, 0, 0, 0, 148, 0, 0, 2, 73, 32, 140, 0, 0

namespace Test
{
	TEST_CLASS(ModelTests)
	{
	public:

		TEST_METHOD(testDraftDeck)
		{
			TestStaticDataManager staticDataManager{ 200 };
			DraftDeck draftDeck{ staticDataManager, 69 };
			
			vector<string> expectedValues{ "test_187", "test_0", "test_129" };
			const Card* cardPointer{ nullptr };
			size_t expectedCardsLeft = 100;
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
			TestStaticDataManager staticDataManager{ 200 };
			DraftDeck draftDeck{ staticDataManager, 69 };
			DraftPile draftPile{ draftDeck };

			// Draft pile should start with 1 pile
			Assert::AreEqual((size_t)1, draftPile.cardsInPile().size());

			const Card* draftedCard{ nullptr };

			// Add 1 extra card then draft the 2nd card
			draftPile.addCardToPile();
			draftedCard = draftPile.draftCardAtIndex(1);
			Assert::AreEqual(string{ "test_0" }, draftedCard->id());

			// Add an extra card, the draft the first card in pile
			draftPile.addCardToPile();
			Assert::AreEqual((size_t)2, draftPile.cardsInPile().size());
			draftedCard = draftPile.draftCardAtIndex(0);
			Assert::AreEqual(string{ "test_129" }, draftedCard->id());
		}

		TEST_METHOD(testDraftingCommands)
		{
			TestStaticDataManager staticDataManager{ 200 };
			GameState gameState{ staticDataManager, "player0", "player1", 0, 69 };
			AbstractCommandProcessor AbstractCommandProcessor{ gameState };

			const DraftPile& firstPile = gameState.draftBoard().piles().at(0);
			const DraftPile& secondPile = gameState.draftBoard().piles().at(1);
			const DraftPile& thirdPile = gameState.draftBoard().piles().at(2);

			// Start a draft for player 0, skip the first pile
			AbstractCommandProcessor.ProcessCommandFromClient(DraftSkipPileCommand{ gameState.phaseStack().getCurrentPhase().playerIndex });
			Assert::AreEqual((size_t)2, firstPile.cardsInPile().size());
			Assert::AreEqual(string{ "test_0" }, firstPile.cardsInPile().at(1)->id());
			// Then draft the card in the 2nd pile
			AbstractCommandProcessor.ProcessCommandFromClient(DraftAtIndexCommand{ gameState.phaseStack().getCurrentPhase().playerIndex, 0});
			auto player0Cards = gameState.playerAtIndex(0).cardsInHand();
			Assert::AreEqual((size_t)1, player0Cards.size());
			Assert::AreEqual(string{ "test_0" }, player0Cards.at(0)->id());
			Assert::AreEqual((unsigned int)1, gameState.phaseStack().getCurrentPhase().playerIndex); // Should move to the next players draft phase

			// Next the second player will skip every pile and take from top
			AbstractCommandProcessor.ProcessCommandFromClient(DraftSkipPileCommand{ gameState.phaseStack().getCurrentPhase().playerIndex });
			Assert::AreEqual((size_t)3, firstPile.cardsInPile().size());
			AbstractCommandProcessor.ProcessCommandFromClient(DraftSkipPileCommand{ gameState.phaseStack().getCurrentPhase().playerIndex });
			Assert::AreEqual((size_t)2, secondPile.cardsInPile().size());
			Assert::AreEqual(string{ "test_148" }, secondPile.cardsInPile().at(1)->id());
			AbstractCommandProcessor.ProcessCommandFromClient(DraftSkipPileCommand{ gameState.phaseStack().getCurrentPhase().playerIndex });
			Assert::AreEqual((size_t)2, thirdPile.cardsInPile().size());
			Assert::AreEqual(string{ "test_0" }, thirdPile.cardsInPile().at(1)->id());
			auto player1Cards = gameState.playerAtIndex(1).cardsInHand();
			Assert::AreEqual((size_t)1, player1Cards.size());
			Assert::AreEqual(string{ "test_0" }, player1Cards.at(0)->id());
			Assert::AreEqual((unsigned int)0, gameState.phaseStack().getCurrentPhase().playerIndex); // Should move to the next players draft phase
		}
	};
}
