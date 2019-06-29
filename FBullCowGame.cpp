#include "FBullCowGame.h"

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLenght() const { return MyHiddenWord.length(); }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";

	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	return;
}

bool FBullCowGame::IsGameWon() const
{
	return false;
}

EWordStatus FBullCowGame::CheckGuessValidity(FString) const
{
	return EWordStatus::OK; //TODO make actual error
}

// receives a VALID guess, intriments turn and returns count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	//inriment the turn number
	MyCurrentTry++;

	// setup a return variable
	FBullCowCount BullCowCount;

	// loop through all letters in the guess
	int32 HiddenWOrldLenght = MyHiddenWord.length();
	for (int32 MHWChar = 0; MHWChar < HiddenWOrldLenght; MHWChar++) {
		//compare letters againts the hidden word
		for (int32 GChar = 0; GChar < Guess.length(); GChar++) {
				//if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) { //if they,re in the same place
					BullCowCount.Bulls++; //incriments bulls
				}
				else {
					BullCowCount.Cows++; //must be a cow
				}
			}
		}
	}
	return BullCowCount;
}
