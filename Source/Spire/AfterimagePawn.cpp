// Fill out your copyright notice in the Description page of Project Settings.


#include "AfterimagePawn.h"
#include "FighterState.h"

void AAfterimagePawn::BeginPlay()
{
	Super::BeginPlay();

	Disappear();
}

void AAfterimagePawn::Appear()
{
	if (!FighterOwner)
		return;

	SetActorTickEnabled(true);

	// Set the current state
	EnterState(FighterOwner->GetCurrentState());
	if (CurrentState == EFighterState::Attack)
		EnterNormalAttackState(FighterOwner->GetCurrentAttack());
	CurrentFrame = FighterOwner->GetCurrentFrame();

	// Set the location, rotation, and velocity
	SetActorLocationAndRotation(FighterOwner->GetActorLocation(), FighterOwner->GetActorQuat());
	Velocity = FighterOwner->Velocity;

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::FromHex("#FF80FFFF"), TEXT("Afterimage"));
}

void AAfterimagePawn::Disappear()
{
	SetActorLocation(FVector(0.0, 4000.0, 0.0));

	SetActorTickEnabled(false);
}

void AAfterimagePawn::EnterState(EFighterState State)
{
	if (State != EFighterState::Attack)
		Disappear();

	Super::EnterState(State);
}

void AAfterimagePawn::EnterNormalAttackState(UFighterAttackAsset* AttackAsset)
{
	Super::EnterNormalAttackState(AttackAsset);
}

void AAfterimagePawn::TakeHit(AFighterPawn* Attacker, float Damage)
{
	if (Attacker != GetOwner()) {
		Disappear();
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Owner Hit")));
	}
}
