// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FighterState.generated.h"

class UFighterAttackAsset;

/**
 * 
 */
UCLASS()
class FIGHTER_API UFighterState : public UObject
{
	GENERATED_BODY()

public:
	// When the fighter enters this state, Animationwill play until the state ends.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	UAnimSequence* Animation;
	// When the attack button is pressed, the fighter will enter this state.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attack")
	UFighterAttackAsset* Attack;
};
