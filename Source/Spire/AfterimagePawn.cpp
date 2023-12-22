// Fill out your copyright notice in the Description page of Project Settings.


#include "AfterimagePawn.h"
#include "FighterStateAsset.h"

void AAfterimagePawn::Disappear()
{
	SetActorLocation(FVector(0.0, 4000.0, 0.0));
}

void AAfterimagePawn::EnterState(UFighterStateAsset* State, EVelocityType VelocityType, bool bResetAnimation, bool bSplit)
{
	if (!State->bIsAttack) {
		Disappear();
	}

	Super::EnterState(State, VelocityType, bResetAnimation, bSplit);
}

void AAfterimagePawn::TakeHit(AFighterPawn* Attacker, float Damage)
{
	if (Attacker != GetOwner()) {
		Disappear();
	}
}
