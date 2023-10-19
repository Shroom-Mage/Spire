// Fill out your copyright notice in the Description page of Project Settings.


#include "FightingComponent.h"

// Sets default values for this component's properties
UFightingComponent::UFightingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UFightingComponent::EnterStateTransition(UFighterStateAsset* State, EVelocityType VelocityType, bool bResetAnimation, bool bSplit)
{
	if (State == CurrentState)
		return;

	CurrentState = State;

	// Play animation
	if (State->Animation != CurrentAnimation || bResetAnimation) {
		CurrentAnimation = State->Animation;
		OwnerSkeletalMesh->PlayAnimation(State->Animation, State->bLoopAnimation);
	}

	// Adjust body box
	FVector BodyBoxLocation = FVector(CurrentState->BodyBoxLocation.X, 0.0f, CurrentState->BodyBoxLocation.Y);
	FVector BodyBoxExtent = FVector(CurrentState->BodyBoxExtent.X, 0.0f, CurrentState->BodyBoxExtent.Y);
	OwnerBodyBox->SetRelativeLocation(BodyBoxLocation);
	OwnerBodyBox->SetBoxExtent(BodyBoxExtent);

	// Adjust attack box
	FVector AttackBoxLocation = FVector(CurrentState->AttackBoxLocation.X, 0.0f, CurrentState->AttackBoxLocation.Y);
	FVector AttackBoxExtent = FVector(CurrentState->AttackBoxExtent.X, 0.0f, CurrentState->AttackBoxExtent.Y);
	OwnerAttackBox->SetRelativeLocation(AttackBoxLocation);
	OwnerAttackBox->SetBoxExtent(AttackBoxExtent);

	// Apply initial velocity
	switch (VelocityType) {
	case EVelocityType::ADD:
		Velocity += CurrentState->VelocityInitial;
		break;
	case EVelocityType::REPLACE:
		Velocity = CurrentState->VelocityInitial;
		break;
	default:
		break;
	}

	// Reset time
	if (!bSplit)
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

	// Update timers
	StateTime += DeltaTime;
	JumpInputTime -= DeltaTime;
	EvadeInputTime -= DeltaTime;
	NormalInputTime -= DeltaTime;
	SpecialInputTime -= DeltaTime;

	// Set attack activity
	if (StateTime > CurrentState->ActiveStartTime && StateTime < CurrentState->ActiveEndTime) {
		bIsAttackActive = true;
		OwnerBodyBox->ShapeColor.A = 255;
	}
	else {
		bIsAttackActive = false;
		OwnerBodyBox->ShapeColor.A = 0;
	}

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

	// Cancel state
	if (CurrentState->CancelTime > 0.0f
		&& StateTime > CurrentState->CancelTime
		&& (MovementInput < 0.0f
			|| MovementInput > 0.0f
			|| JumpInputTime > 0.0f
			|| EvadeInputTime > 0.0f
			|| NormalInputTime > 0.0f
			|| SpecialInputTime > 0.0f))
	{
		if (bTouchedGround)
			CurrentState = StandingNeutral;
		else
			CurrentState = AirNeutral;
	}

	// Enter this state's normal attack if attempting to attack
	if (NormalInputTime > 0.0f
		&& CurrentState->AttackNormal)
	{
		NormalInputTime = 0.0f;
		EnterStateTransition(CurrentState->AttackNormal, EVelocityType::ADD, true);
	}
	// Enter Air state if attempting to jump while touching the ground
	if ((CurrentState == StandingNeutral
			|| CurrentState == StandingForward
			|| CurrentState == StandingBackward)
		&& bTouchedGround
		&& JumpInputTime > 0.0f
		&& AirNeutral)
	{
		JumpInputTime = 0.0f;
		EnterStateTransition(AirNeutral, EVelocityType::ADD);
		return;
	}
	// Enter Landing state if the ground is touched from the air
	if ((CurrentState == AirNeutral
			|| CurrentState == AirForward
			|| CurrentState == AirBackward)
		&& bTouchedGround
		&& StandingNeutral)
	{
		EnterStateTransition(StandingNeutral, EVelocityType::ADD);
		return;
	}
	// Enter StandingForward state if attempting to move while standing
	if ((CurrentState == StandingNeutral
			|| CurrentState == StandingForward
			|| CurrentState == StandingBackward)
		&& MovementInput > 0.0f
		&& StandingForward)
	{
		EnterStateTransition(StandingForward, EVelocityType::IGNORE);
		return;
	}
	// Enter StandingBackward state if attempting to move while standing
	if ((CurrentState == StandingNeutral
			|| CurrentState == StandingForward
			|| CurrentState == StandingBackward)
		&& MovementInput < 0.0f
		&& StandingBackward)
	{
		EnterStateTransition(StandingBackward, EVelocityType::IGNORE);
		return;
	}
	// Enter StandingNeutral state if not attempting to move while standing
	if ((CurrentState == StandingNeutral
			|| CurrentState == StandingForward
			|| CurrentState == StandingBackward)
		&& MovementInput == 0.0f
		&& StandingNeutral)
	{
		EnterStateTransition(StandingNeutral, EVelocityType::IGNORE);
		return;
	}
	// Enter AirForward state if attempting to move while Air
	if ((CurrentState == AirNeutral
			|| CurrentState == AirBackward)
		&& MovementInput > 0.0f
		&& AirForward)
	{
		EnterStateTransition(AirForward, EVelocityType::IGNORE);
		return;
	}
	// Enter AirBackward state if attempting to move while Air
	if ((CurrentState == AirNeutral
			|| CurrentState == AirForward)
		&& MovementInput < 0.0f
		&& AirBackward)
	{
		EnterStateTransition(AirBackward, EVelocityType::IGNORE);
		return;
	}
	// Enter AirNeutral state if not attempting to move while Air
	if ((CurrentState == AirForward
			|| CurrentState == AirBackward)
		&& MovementInput == 0.0f
		&& AirNeutral)
	{
		EnterStateTransition(AirNeutral, EVelocityType::IGNORE);
		return;
	}
	// Enter End state if Duration was reached
	if (CurrentState->Duration > 0.0f
		&& StateTime >= CurrentState->Duration
		&& CurrentState->End)
	{
		EnterStateTransition(CurrentState->End, EVelocityType::IGNORE);
		return;
	}
}

void UFightingComponent::SetBodyBox(UBoxComponent* BodyBox)
{
	OwnerBodyBox = BodyBox;
}

void UFightingComponent::SetAttackBox(UBoxComponent* AttackBox)
{
	OwnerAttackBox = AttackBox;
}

void UFightingComponent::SetSkeletalMesh(USkeletalMeshComponent* SkeletalMesh)
{
	OwnerSkeletalMesh = SkeletalMesh;
}

void UFightingComponent::Move(float Value)
{
	MovementInput = Value;
}

void UFightingComponent::Jump()
{
	JumpInputTime = 0.25f;
}

void UFightingComponent::Evade()
{
	EvadeInputTime = 0.5f;
}

void UFightingComponent::Normal()
{
	NormalInputTime = 0.5f;
}

void UFightingComponent::Special()
{
	SpecialInputTime = 0.5f;
}
