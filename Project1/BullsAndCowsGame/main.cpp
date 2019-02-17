/* This is the console executable that makes use of th BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/
#pragma once
#include "FBullCowGame.h";
#include <iostream>
#include <string>

//to make syntax Unreal friendly
using int32 = int;
using FText = std::string;


void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();


FBullCowGame BCGame;//Instantiate a new game which we reuse across plays

int main()
{   	
	do
	{
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());
	return 0; //exit the application
}

//Plays a single game to completion
void PlayGame()
{
	BCGame.Reset(); //resets the game instance to its initial state
	int32 MaxTries=BCGame.GetMaxTries(); 
	FText Guess;
	do
	{
		{
			Guess = GetValidGuess(); //gets a guess, checks if its a valid guess, if not return a statement of what should be done else return the Guess
			FBullCowCount BullCowCount = BCGame.SubmitValidGues(Guess); //fixes the number of bulls and cows of the current guess
			//submit valid guess to the game
			std::cout << "Bulls = " << BullCowCount.Bulls;
			std::cout << ". Cows = " << BullCowCount.Cows;//print the number of bulls and cows
			if(MaxTries - BCGame.GetCurrentTry() + 1> 0 && BullCowCount.Bulls!=6)
				std::cout << "\nYou've left only " << MaxTries - BCGame.GetCurrentTry() + 1 << " guesses left.\n \n";//print number of tries left
		}
	} while (!BCGame.IsGameWon() && MaxTries>=BCGame.GetCurrentTry());// do this until game is won or player is all out of tries
	PrintGameSummary();// prints game summary
}


void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "\n\nGood job, you won!!! Congratulations!\n\n";
	}
	else
	{
		std::cout << "\n\nSorry, you lost. But hey, you can try again :). Better luck next time!\n\n";
	}
}


bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? ";
	FText Response;
	getline(std::cin, Response);
	if (Response[0] == 'y' || Response[0] == 'Y')
	{
		std::cout << std::endl;
		return true;
	}
	return false;
}
//loop continually until user gives valid guess
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess;
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << ". \n";
		std::cout << "Enter your guess:" << std::endl;

		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "All the letters of the guess should be lowercase!!\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		default:
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);
	return Guess;
}

void PrintIntro()
{
	std::cout << "  Welcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "   }....{                            L....L\n";
	std::cout << "   ( o o)                            (O O  )\n";
	std::cout << "   \\   /                              \\   /\n";
	std::cout << "    ^__^                              ('_')\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of\n\n";
}