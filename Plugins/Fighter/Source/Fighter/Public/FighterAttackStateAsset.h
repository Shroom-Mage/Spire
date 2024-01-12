// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FighterStateAsset.h"
#include "FighterAttackStateAsset.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTER_API UFighterAttackStateAsset : public UFighterStateAsset
{
	GENERATED_BODY()
	
public:
	UFighterAttackStateAsset();

public:
	// The state time at which the attack box becomes active.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Timing")
	float ActiveStartTime = 0.0f;
	// The state time at which the attack box becomes inactive.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Timing")
	float ActiveEndTime = 0.0f;
	// When CancelTime is reached (in seconds), the state may be changed.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Timing")
	float CancelTime = 0.0f;
	// The location of the attack collider.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Collision")
	FVector2D AttackBoxLocation;
	// The extent of the attack collider.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Collision")
	FVector2D AttackBoxExtent;
	// The animation to play when entering the state.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	UAnimSequence* AnimationLead;
	// The animation to play when entering the state.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	UAnimSequence* AnimationFollow;
};
