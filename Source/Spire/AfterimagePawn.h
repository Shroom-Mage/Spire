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
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EnterState(EFighterState State) override;

	virtual void EnterNormalAttackState(UFighterAttackAsset* AttackAsset) override;

public:
	UFUNCTION(BlueprintCallable)
	void Appear();

	UFUNCTION(BlueprintCallable)
	void Disappear();

	virtual void TakeHit(AFighterPawn* Attacker, float Damage) override;

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	AFighterPawn* FighterOwner;
};
