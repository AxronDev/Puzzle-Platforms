// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "PuzzlePlatformsGameInstance.generated.h"

class UUserWidget;
class UMainMenu;
class UPauseMenu;

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
	
	UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init();
	
	UFUNCTION(BlueprintCallable)
	void LoadMenu();


	UFUNCTION()
	void Host();

	UFUNCTION()
	void Join(const FString& Address);

	UFUNCTION()
	void QuitSession();

private:
	TSubclassOf<UUserWidget> MenuClass;
	TSubclassOf<UUserWidget> PauseMenuClass;
	
	UMainMenu* Menu;
	UPauseMenu* PauseMenu;

public:
	UFUNCTION(BlueprintCallable)
	virtual void LoadPauseMenu();
};
