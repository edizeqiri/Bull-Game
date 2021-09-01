// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
	Super::BeginPlay();
	
	SetupGame();

	PrintLine(FString::Printf(TEXT("The HiddenWord is: %s"), *HiddenWord)); // Debug line

	const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
	FFileHelper::LoadFileToStringArray(Words, *WordListPath);
	PrintLine(TEXT("The number of words is: %i"),Words.Num());
	PrintLine(TEXT("The number of valid words is: %i"),GetValidWords(Words).Num());
	
	
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
	/* if game is over do CLeanScreen and SetupGame()
	 else check Player Guess*/


	if (bGameOver)
	{
		ClearScreen();
		SetupGame();
	}
	else
	{
		ProcessGuess(Input, Lives);
	}
}

void UBullCowCartridge::SetupGame()
{
	// Welcome the Player
	PrintLine(TEXT("Welcome to Bulls Game!"));

	HiddenWord = TEXT("head");
	Lives = HiddenWord.Len();

	PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
	PrintLine(TEXT("You have %i lives!"), Lives);
	PrintLine(TEXT("Type in your guess.\nPress Enter to Play!"));
	bGameOver = false;
}

void UBullCowCartridge::EndGame()
{
	bGameOver = true;

	PrintLine(TEXT("\nPress Enter to play again!"));
}

void UBullCowCartridge::ProcessGuess(const FString Guess, int32 Counter)
{
	if (Guess == HiddenWord)
	{
		PrintLine(TEXT("You Won!"));
		EndGame();
		return;
	}


	if (HiddenWord.Len() != Guess.Len())
	{
		PrintLine(TEXT("The Hidden Word is %i characters long. Try again!"), HiddenWord.Len());
		return;
	}

	if (!IsIsogram(Guess))
	{
		PrintLine(TEXT("No repeating letters, try again!"));
		return;
	}

	--Lives;

	PrintLine(TEXT("You have %i lives remaining. Try again!"), Lives);
	if (!(Lives > 0))
	{
		ClearScreen();
		PrintLine(TEXT("You have no lives left!"));
		PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
		EndGame();
		return;
	}
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
	for (int32 i = 0; i < Word.Len(); i++)
	{
		for (int32 j = i+1; j < Word.Len(); j++)
		{
			if (Word[i] == Word[j])
			{
				return false;
			}
		}
	}
	return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(TArray<FString> List) const
{
	TArray<FString> ValidWords;

	for (int32 i = 0; i < List.Num(); i++)
	{
		if(List[i].Len() >= 4 && List[i].Len() <= 8 && IsIsogram(List[i]))
		{
			ValidWords.Emplace(List[i]);
		}
	}
	return ValidWords;
}
