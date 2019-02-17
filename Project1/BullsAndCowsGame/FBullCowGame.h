/* 
The game logic(no view code or direcrt user interaction
The game is a simple guess the word game based on mastermind.
*/

#pragma once
#include <string>
// making the syntax Unreal Friendly
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
	Wrong_Length,
	Not_Lowercase
};


class FBullCowGame
{

public:
	FBullCowGame();//constructor
	int32 GetCurrentTry() const;
	int32 GetMaxTries() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon()const;

	EGuessStatus CheckGuessValidity(FString) const; 
	void Reset(); 
	void GiveInfo();
	FBullCowCount SubmitValidGues(FString);


private:
	//see constructur for initialization
	bool bGameIsWon;
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;

	bool IsIsogram(FString Guess)const;
	bool IsLowercase(FString) const;
};