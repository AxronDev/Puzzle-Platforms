// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer) 
{
     UE_LOG(LogTemp, Warning, TEXT("Constructor Function Call"));
}

void UPuzzlePlatformsGameInstance::Init() 
{
     UE_LOG(LogTemp, Warning, TEXT("Init Function Call"));
}

void UPuzzlePlatformsGameInstance::Host() 
{
     UEngine* Engine = GetEngine();
     if (ensure(!Engine)) return;

     Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address) 
{
     UEngine* Engine = GetEngine();
     if (ensure(!Engine)) return;

     Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));
}

