#include "FBullCowGame.h"

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLenght() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const{ return bGameIsWon; }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";

	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (false)// if the guess isnt an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (false) //if guess isnt all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLenght())	//if the guess lenght is wrong
	{
		return EGuessStatus::Wrong_Lenght;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

// receives a VALID guess, intriments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WorldLenght = MyHiddenWord.length(); // assuming same lenght as guess

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WorldLenght; MHWChar++) {
		//compare letters againts the guess
		for (int32 GChar = 0; GChar < WorldLenght; GChar++) {
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
	if (BullCowCount.Bulls == WorldLenght) 
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}
