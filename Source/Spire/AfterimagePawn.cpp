// Fill out your copyright notice in the Description page of Project Settings.


#include "AfterimagePawn.h"
#include "FighterState.h"

void AAfterimagePawn::Disappear()
{
	SetActorLocation(FVector(0.0, 4000.0, 0.0));
}

void AAfterimagePawn::EnterState(UFighterState* State)
{
	//if (!State->GetIsAttack()) {
	//	Disappear();
	//}

	Super::EnterState(State);
}

void AAfterimagePawn::TakeHit(AFighterPawn* Attacker, float Damage)
{
	if (Attacker != Owner) {
		Disappear();
	}
}
