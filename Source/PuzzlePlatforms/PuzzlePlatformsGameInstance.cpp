// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "PlatformTrigger.h"
#include "MenuSystem/MainMenu.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer) 
{
     ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
     if(MenuBPClass.Class != nullptr)
          MenuClass = MenuBPClass.Class;
}

void UPuzzlePlatformsGameInstance::Init() 
{
     UE_LOG(LogTemp, Warning, TEXT("%s"), *MenuClass->GetName());
}

void UPuzzlePlatformsGameInstance::LoadMenu() 
{
     Menu = CreateWidget<UMainMenu>(this, MenuClass);
     if (!ensure(Menu)) return;
     
     Menu->Setup();

     Menu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::Host() 
{
     if (Menu) 
     {
          Menu->Teardown();
     }
     UEngine* Engine = GetEngine();
     if (!ensure(Engine)) return;

     Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

     UWorld* World = GetWorld(); 
     if(!ensure(World)) return;
     World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address) 
{
     if (Menu) 
     {
          Menu->Teardown();
     }
     UEngine* Engine = GetEngine();
     if (ensure(!Engine)) return;

     Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

     APlayerController* PlayerController = GetFirstLocalPlayerController();
     if(ensure(!PlayerController)) return;

     PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

