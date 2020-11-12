// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "PlatformTrigger.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/PauseMenu.h"
#include "Kismet/KismetSystemLibrary.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer) 
{
     ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
     if(MenuBPClass.Class != nullptr)
          MenuClass = MenuBPClass.Class;

     ConstructorHelpers::FClassFinder<UUserWidget> PauseMenuBPClass(TEXT("/Game/MenuSystem/WBP_PauseMenu"));
     if(PauseMenuBPClass.Class != nullptr)
          PauseMenuClass = PauseMenuBPClass.Class;
}

void UPuzzlePlatformsGameInstance::Init() 
{
     UE_LOG(LogTemp, Warning, TEXT("%s"), *MenuClass->GetName());
     PlayerController = GetFirstLocalPlayerController();
}

void UPuzzlePlatformsGameInstance::LoadMenu() 
{
     Menu = CreateWidget<UMainMenu>(this, MenuClass);
     if (!ensure(Menu)) return;
     
     Menu->Setup();

     Menu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::LoadPauseMenu() 
{
     PauseMenu = CreateWidget<UPauseMenu>(this, PauseMenuClass);
     if (!ensure(PauseMenu)) return;
     
     PauseMenu->Setup();

     PauseMenu->SetMenuInterface(this);
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
     if (!ensure(Engine)) return;

     Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

     if(!ensure(PlayerController)) return;
     Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Player controller is good")));

     PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformsGameInstance::QuitSession() 
{
     PauseMenu->Teardown();
     ReturnToMainMenu();
}

void UPuzzlePlatformsGameInstance::QuitGame() 
{
     if(!ensure(PlayerController)) return;

     PlayerController->ConsoleCommand("Quit", false);
}

