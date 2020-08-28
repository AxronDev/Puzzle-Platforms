// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "GameFramework/MovementComponent.h"

AMovingPlatform::AMovingPlatform() 
{
    PrimaryActorTick.bCanEverTick = true;
    SetMobility(EComponentMobility::Movable);

    // MovementComponent = CreateDefaultSubobject<UMovementComponent>("MovementComponent");
}

void AMovingPlatform::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);

    if(HasAuthority())
    {
        FVector Location = GetActorLocation();
        Location += FVector(Speed * DeltaTime, 0, 0);
        SetActorLocation(Location);
    }
}
