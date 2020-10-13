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

     UWorld* World = GetWorld();
     if(ensure(!World)) return;
     World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address) 
{
     UEngine* Engine = GetEngine();
     if (ensure(!Engine)) return;

     Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

     APlayerController* PlayerController = GetFirstLocalPlayerController();
     if(ensure(!PlayerController)) return;

     PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

