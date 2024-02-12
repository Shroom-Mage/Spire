// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FighterState.h"
#include "FighterAttackAsset.h"
#include "FighterAttackState.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTER_API UFighterAttackState : public UFighterState
{
	GENERATED_BODY()
	
public:
	// The asset used for attack properties
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Asset")
	UFighterAttackAsset* Asset;
};
