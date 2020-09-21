// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "GameFramework/MovementComponent.h"

AMovingPlatform::AMovingPlatform() 
{
    PrimaryActorTick.bCanEverTick = true;
    SetMobility(EComponentMobility::Movable);

    // MovementComponent = CreateDefaultSubobject<UMovementComponent>("MovementComponent");
}

void AMovingPlatform::BeginPlay() 
{
    Super::BeginPlay();

    if(HasAuthority())
    {
        SetReplicates(true);
        SetReplicateMovement(true);
    }

    GlobalStartLocation = GetActorLocation();
    GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::AddActiveTrigger() 
{
    ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger() 
{
    ActiveTriggers--;
}

void AMovingPlatform::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);

    if(HasAuthority())
    {
        if(ActiveTriggers > 0)
        {
            FVector Location = GetActorLocation();
            float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
            float JourneyTravled = (Location - GlobalStartLocation).Size();

            if (JourneyTravled >= JourneyLength) 
            {
                FVector Buffer = GlobalStartLocation;
                GlobalStartLocation = GlobalTargetLocation;
                GlobalTargetLocation = Buffer;
            }
            
            FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
            Location += Direction * (Speed * DeltaTime);
            SetActorLocation(Location);
        }
    }
}
