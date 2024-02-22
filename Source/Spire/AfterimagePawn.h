// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FighterPawn.h"
#include "AfterimagePawn.generated.h"

/**
 * 
 */
UCLASS()
class SPIRE_API AAfterimagePawn : public AFighterPawn
{
	GENERATED_BODY()
	
private:
	void Disappear();

protected:
	virtual void EnterState(EFighterState State) override;

public:
	virtual void TakeHit(AFighterPawn* Attacker, float Damage) override;
};
