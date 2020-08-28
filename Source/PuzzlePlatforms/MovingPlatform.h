// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

class UMovementComponent;

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	AMovingPlatform();

	UPROPERTY(EditAnywhere)
	float Speed = 10;

protected:
	virtual void Tick(float DeltaSeconds) override;

private:
	UMovementComponent* MovementComponent;
	
};
