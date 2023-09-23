// Fill out your copyright notice in the Description page of Project Settings.


#include "FightingComponent.h"
#include "FighterStateAsset.h"

// Sets default values for this component's properties
UFightingComponent::UFightingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UFightingComponent::MoveForward()
{
	EnterState(CurrentState->Forward);
}

void UFightingComponent::MoveBackward()
{
	EnterState(CurrentState->Backward);
}

// Called to enter a new state. Entering the current state will do nothing.
void UFightingComponent::EnterState(UFighterStateAsset* State)
{
	if (State == CurrentState)
		return;

	CurrentState = State;

	// Apply initial velocity
	if (CurrentState->bInheritVelocity)
		Velocity += CurrentState->VelocityInitial;
	else
		Velocity = CurrentState->VelocityInitial;

	// Reset time
	StateTime = 0.0f;
}


// Called when the game starts
void UFightingComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UFightingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	StateTime += DeltaTime;

	// Approach target velocity
	if (Velocity < CurrentState->VelocityTarget - CurrentState->Acceleration) {
		Velocity += CurrentState->Acceleration * DeltaTime;
	}
	else if (Velocity > CurrentState->VelocityTarget + CurrentState->Acceleration) {
		Velocity -= CurrentState->Acceleration * DeltaTime;
	}
	else {
		Velocity = CurrentState->VelocityTarget;
	}

	// Translate
	AActor* Owner = GetOwner();
	FVector Location = Owner->GetActorLocation();
	FVector Destination = Location + FVector(Velocity.X, Velocity.Y, 0.0f);
	Owner->SetActorLocation(Destination);

	// End state if time has reached duration
	if (CurrentState->Duration && CurrentState->End && StateTime >= CurrentState->Duration) {
		EnterState(CurrentState->End);
	}
}

