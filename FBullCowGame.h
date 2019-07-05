#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus 
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Lenght,
	Not_Lowercase,
};

class FBullCowGame {
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLenght() const;

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; // TODO make a more rich return value.

	void Reset(); // TODO make a more rich return value.
	FBullCowCount SubmitValidGuess(FString Guess);


// ^^ Please try and ignore this and focus on the interface above ^^
private:
	// see constructor for initialisation
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;
};