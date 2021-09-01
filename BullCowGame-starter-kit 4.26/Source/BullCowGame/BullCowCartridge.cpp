// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Math/UnrealMathUtility.h"


void UBullCowCartridge::BeginPlay() // When the game starts
{
	Super::BeginPlay();

	const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
	FFileHelper::LoadFileToStringArrayWithPredicate(Isograms, *WordListPath, [](const FString& Word)
	{
		return Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word);
	});

	SetupGame();

	
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
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
		ProcessGuess(PlayerInput, Lives);
	}
}

void UBullCowCartridge::SetupGame()
{
	HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
	Lives = HiddenWord.Len() * 2;
	bGameOver = false;

	PrintLine(TEXT("Welcome to Bulls Game!"));
	PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
	PrintLine(TEXT("You have %i lives!"), Lives);
	PrintLine(TEXT("Type in your guess.\nPress Enter to Play!"));
	PrintLine(TEXT("If you need help type 'help'!"));

	PrintLine(FString::Printf(TEXT("The HiddenWord is: %s"), *HiddenWord)); // Debug line
}

void UBullCowCartridge::EndGame()
{
	bGameOver = true;

	PrintLine(TEXT("\nPress Enter to play again!"));
	SetupGame();
}

void UBullCowCartridge::ProcessGuess(const FString& Guess, int32 Counter)
{
	if (Guess == TEXT("Help"))
	{
		PrintLine(TEXT("You get a Cow for a right Character and \na Bull for a right Character at \nthe right spot!"));
		return;
	}
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
	
	FBullCowCount Score = GetBullCows(Guess);

	PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);

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

bool UBullCowCartridge::IsIsogram(const FString& Word)
{
	for (int32 i = 0; i < Word.Len(); i++)
	{
		for (int32 j = i + 1; j < Word.Len(); j++)
		{
			if (Word[i] == Word[j])
			{
				return false;
			}
		}
	}
	return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& List)
{
	TArray<FString> ValidWords;

	for (FString Word : List)
	{
		if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
		{
			ValidWords.Emplace(Word);
		}
	}
	return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
	FBullCowCount Count;

	for (int32 i = 0; i < Guess.Len(); i++)
	{
		if (Guess[i] == HiddenWord[i])
		{
			Count.Bulls++;
			continue;
		}

		for (int32 j = 0; j < Guess.Len(); j++)
		{
			if (Guess[i] == HiddenWord[j])
			{
				Count.Cows++;
				break;
			}
		}
	}
	return Count;
}
