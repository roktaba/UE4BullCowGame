#pragma once

#include "FBullCowGame.h"
#include <map>

// to make syntax Unreal friendly
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } //default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLenght() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const{ return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLenghtToMaxTries{ {3,5}, {4,7}, {5,10}, {6,15}, {7,20} };
	return WordLenghtToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "plane"; // this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))// if the guess isnt an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess)) //if guess isnt all lowercase
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

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;//setup out map
	for (auto Letter : Word) // for all letters of the word
	{
		Letter = tolower(Letter); //handle mixed case
			if (LetterSeen[Letter]) //if the letter is in the map
			{
				return false;
			}
			else
			{
					LetterSeen[Letter] = true; 	//add the letter to the map as seen
			}
	}

	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))// if not a lowercse letter
		{
			return false;
		}
	}
	return true;
}
