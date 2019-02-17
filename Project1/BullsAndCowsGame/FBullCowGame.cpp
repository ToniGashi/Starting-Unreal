#pragma once
#include "FBullCowGame.h"
#include <map>
//make syntax Unreal Friendly
#define TMap std::map
using int32 = int;


FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetCurrentTry() const{return MyCurrentTry;}
int FBullCowGame::GetMaxTries() const{
	TMap<int32, int32> WordLengthToMaxTries{ {3,5},{4,5},{5,10},{6,14}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];

}
int32 FBullCowGame::GetHiddenWordLength() const{return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon() const
{
	return bGameIsWon;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	TMap<char, bool> myMap;
	for (auto Letter : Guess)
	{
		Letter = tolower(Letter);
		if (myMap[Letter])
		{
			return false;
		}
		else
		{
			myMap[Letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Guess) const
{
	for (auto Letter : Guess)
	{
		if (isupper(Letter))
			return false;

	}
	return true;
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "fly"; //must be an isogram
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
}



void FBullCowGame::GiveInfo()
{
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))//if the guess isn't isogram,return error
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))//if the guess isn't all lowercase,return error
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != MyHiddenWord.length())//if the guess length is wrong, return error
	{
		return EGuessStatus::Wrong_Length;
	}
	else 
	{
		return EGuessStatus::OK;
	}//else return OK
}
// receives a VALID guess, incriments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGues(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();	
///loop through all letter in the Hidden word	
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		//compare letters against the Guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			//if they match then
			if (Guess[MHWChar] == MyHiddenWord[GChar])
			{
				//increment bulls if they're in the same place
				if (MHWChar == GChar)
					BullCowCount.Bulls++;
				//increment cows if not
				else
					BullCowCount.Cows++;
			}
		} 
	}
	
	if (BullCowCount.Bulls == MyHiddenWord.length()) bGameIsWon = true;  else bGameIsWon = false;


	return BullCowCount;
}

