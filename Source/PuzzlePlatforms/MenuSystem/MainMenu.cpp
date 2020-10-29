// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"

bool UMainMenu::Initialize() 
{
     bool Success = Super::Initialize();
     if(!Success) return false;

     if(!ensure(Host)) return false;
     Host->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

     return true;
}

void UMainMenu::HostServer() 
{
     if(MenuInterface)
     {
          MenuInterface->Host();
     }
}

void UMainMenu::SetMenuInterface(IMenuInterface* MenuInterfaceBase) 
{
     MenuInterface = MenuInterfaceBase;
}

void UMainMenu::Setup() 
{
     this->AddToViewport();

     UWorld* World = GetWorld();
     if(!ensure(World)) return;

     APlayerController* PlayerController = World->GetFirstPlayerController();
     if(!ensure(PlayerController)) return;

     this->bIsFocusable = true;
     FInputModeUIOnly InputModeData;
     InputModeData.SetWidgetToFocus(this->TakeWidget());
     InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

     PlayerController->SetInputMode(InputModeData);

     PlayerController->bShowMouseCursor = true;
}

void UMainMenu::Teardown() 
{
     this->RemoveFromViewport();

     UWorld* World = GetWorld();
     if(!ensure(World)) return;

     APlayerController* PlayerController = World->GetFirstPlayerController();
     if(!ensure(PlayerController)) return;

     FInputModeGameOnly InputModeData;
     PlayerController->SetInputMode(InputModeData);

     PlayerController->bShowMouseCursor = false;
}
