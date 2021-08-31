// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    // Welcome the Player
    PrintLine(TEXT("Welcome to Bulls Game!"));
    PrintLine(TEXT("Guess the 4 letter word!")); // Remove number to variable
    PrintLine(TEXT("Press Enter to Play!"));

    // Setting up the Game
    InitGame();
    

}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
     
    // Checking Player Guess
    if (Input == HiddenWord)    
    {
        PrintLine(TEXT("You Won!"));

    }
    else
    {
        PrintLine(TEXT("Try again!"));

        // Remove Live
    }
}

void UBullCowCartridge::InitGame()
{
    HiddenWord = TEXT("head");
    Lives = 3;
}

