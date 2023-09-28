// Fill out your copyright notice in the Description page of Project Settings.


#include "FightingComponent.h"

// Sets default values for this component's properties
UFightingComponent::UFightingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UFightingComponent::EnterStateTransition(FFighterStateTransition Transition)
{
	if (!Transition.State || Transition.State == CurrentState)
		return;

	CurrentState = Transition.State;

	// Apply initial velocity
	switch (Transition.InitialVelocity) {
	case VelocityType::ADD:
		Velocity += CurrentState->VelocityInitial;
		break;
	case VelocityType::REPLACE:
		Velocity = CurrentState->VelocityInitial;
		break;
	default:
		break;
	}

	// Reset time
	if (!Transition.bSplit)
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

	if (!CurrentState)
		return;

	StateTime += DeltaTime;

	// Approach target velocity
	if (Velocity.X <= CurrentState->VelocityTarget.X - CurrentState->Acceleration.X * DeltaTime) {
		Velocity.X += CurrentState->Acceleration.X * DeltaTime;
	}
	else if (Velocity.X >= CurrentState->VelocityTarget.X + CurrentState->Deceleration.X * DeltaTime) {
		Velocity.X -= CurrentState->Deceleration.X * DeltaTime;
	}
	else {
		Velocity.X = CurrentState->VelocityTarget.X;
	}
	if (Velocity.Y <= CurrentState->VelocityTarget.Y - CurrentState->Acceleration.Y * DeltaTime) {
		Velocity.Y += CurrentState->Acceleration.Y * DeltaTime;
	}
	else if (Velocity.Y >= CurrentState->VelocityTarget.Y + CurrentState->Deceleration.Y * DeltaTime) {
		Velocity.Y -= CurrentState->Deceleration.Y * DeltaTime;
	}
	else {
		Velocity.Y = CurrentState->VelocityTarget.Y;
	}

	// Translate
	AActor* Owner = GetOwner();
	FVector Location = Owner->GetActorLocation();
	FVector Destination = Location + FVector(Velocity.X, 0.0f, Velocity.Y);
	bool bTouchedGround = Destination.Z <= 0.0;
	if (bTouchedGround) {
		Destination.Z = 0.0;
		Velocity.Y = 0.0;
	}
	Owner->SetActorLocation(Destination);

	// Enter Land state if the ground is touched
	if (bTouchedGround && CurrentState->Land.State) {
		EnterStateTransition(CurrentState->Land);
		return;
	}
	// Enter Forward state if attempting to move
	if (Movement > 0.0f && CurrentState->Forward.State) {
		EnterStateTransition(CurrentState->Forward);
		return;
	}
	// Enter Backward state if attempting to move
	if (Movement < 0.0f && CurrentState->Backward.State) {
		EnterStateTransition(CurrentState->Backward);
		return;
	}
	// Enter End state if time has reached duration
	if (StateTime >= CurrentState->Duration && CurrentState->End.State) {
		EnterStateTransition(CurrentState->End);
		return;
	}
}

void UFightingComponent::Normal()
{
	if (CurrentState && CurrentState->Normal.State)
		EnterStateTransition(CurrentState->Normal);
}

void UFightingComponent::Special()
{
	if (CurrentState && CurrentState->Special.State)
		EnterStateTransition(CurrentState->Special);
}

void UFightingComponent::Move(float Value)
{
	Movement = Value;
}

void UFightingComponent::Jump()
{
	if (CurrentState && CurrentState->Jump.State)
		EnterStateTransition(CurrentState->Jump);
}

void UFightingComponent::Evade()
{
	if (CurrentState && CurrentState->Dodge.State)
		EnterStateTransition(CurrentState->Dodge);
}
