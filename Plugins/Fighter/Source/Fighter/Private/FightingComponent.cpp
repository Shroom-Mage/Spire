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
	if (Transition.bInheritVelocity)
		Velocity += CurrentState->VelocityInitial;
	else
		Velocity = CurrentState->VelocityInitial;

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
	if (Velocity.X < CurrentState->VelocityTarget.X - CurrentState->Acceleration.X) {
		Velocity.X += CurrentState->Acceleration.X * DeltaTime;
	}
	else if (Velocity.X > CurrentState->VelocityTarget.X + CurrentState->Acceleration.X) {
		Velocity.X -= CurrentState->Acceleration.X * DeltaTime;
	}
	else {
		Velocity.X = CurrentState->VelocityTarget.X;
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

	// Enter End state if time has reached duration
	if (CurrentState->Duration && StateTime >= CurrentState->Duration && CurrentState->End.State) {
		EnterStateTransition(CurrentState->End);
		return;
	}
}

void UFightingComponent::AttackNormal()
{
	if (CurrentState && CurrentState->AttackNormal.State)
		EnterStateTransition(CurrentState->AttackNormal);
}

void UFightingComponent::AttackSpecial()
{
	if (CurrentState && CurrentState->AttackSpecial.State)
		EnterStateTransition(CurrentState->AttackSpecial);
}

void UFightingComponent::WalkForward()
{
	if (CurrentState && CurrentState->WalkForward.State)
		EnterStateTransition(CurrentState->WalkForward);
}

void UFightingComponent::WalkBackward()
{
	if (CurrentState && CurrentState->WalkBackward.State)
		EnterStateTransition(CurrentState->WalkBackward);
}

void UFightingComponent::DashForward()
{
	if (CurrentState && CurrentState->DashForward.State)
		EnterStateTransition(CurrentState->DashForward);
}

void UFightingComponent::DashBackward()
{
	if (CurrentState && CurrentState->DashBackward.State)
		EnterStateTransition(CurrentState->DashBackward);
}

void UFightingComponent::Jump()
{
	if (CurrentState && CurrentState->Jump.State)
		EnterStateTransition(CurrentState->Jump);
}

void UFightingComponent::Crouch()
{
	if (CurrentState && CurrentState->Crouch.State)
		EnterStateTransition(CurrentState->Crouch);
}

void UFightingComponent::Dodge()
{
	if (CurrentState && CurrentState->Dodge.State)
		EnterStateTransition(CurrentState->Dodge);
}

void UFightingComponent::Land()
{
	if (CurrentState && CurrentState->Land.State)
		EnterStateTransition(CurrentState->Land);
}
