// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();

    PrintLine(FString::Printf(TEXT("The HiddenWord is: %s"), *HiddenWord)); // Debug line 
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
        if (Input == HiddenWord)    
        {
            PrintLine(TEXT("You Won!"));
            EndGame();
        }
        else
        {
            if(HiddenWord.Len() != Input.Len())
            {
                PrintLine(TEXT("The Hidden Word is %i characters long. You have lost!"), HiddenWord.Len());
                EndGame();
            }

            PrintLine(TEXT("Try again!"));
            // Remove Live
        }
    }
    

    

    
}

void UBullCowCartridge::SetupGame()
{
    // Welcome the Player
    PrintLine(TEXT("Welcome to Bulls Game!"));

    HiddenWord = TEXT("head");
    Lives = 3;

    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len()); 
    PrintLine(TEXT("Type in your guess.\nPress Enter to Play!"));
    // bGameOver = false;

}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press Enter to play again!"));
}

