// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FighterCommand.h"
#include "FighterStateAsset.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTER_API UFighterStateAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float Duration;
	UPROPERTY(EditAnywhere)
	bool bInterruptAnimation;
	UPROPERTY(EditAnywhere)
	bool bInheritVelocity;
	FVector2D Shift;
	UPROPERTY(EditAnywhere)
	FVector2D VelocityInitial;
	UPROPERTY(EditAnywhere)
	FVector2D VelocityTarget;
	UPROPERTY(EditAnywhere)
	FVector2D Acceleration;
	UPROPERTY(EditAnywhere)
	FVector2D Deceleration;
	UPROPERTY(EditAnywhere)
	UFighterStateAsset* AttackNormal;
	UPROPERTY(EditAnywhere)
	UFighterStateAsset* AttackSpecial;
	UPROPERTY(EditAnywhere)
	UFighterStateAsset* Forward;
	UPROPERTY(EditAnywhere)
	UFighterStateAsset* Backward;
	UPROPERTY(EditAnywhere)
	UFighterStateAsset* DashForward;
	UPROPERTY(EditAnywhere)
	UFighterStateAsset* DashBackward;
	UPROPERTY(EditAnywhere)
	UFighterStateAsset* Jump;
	UPROPERTY(EditAnywhere)
	UFighterStateAsset* Crouch;
	UPROPERTY(EditAnywhere)
	UFighterStateAsset* Dodge;
	UPROPERTY(EditAnywhere)
	UFighterStateAsset* Ground;
	UPROPERTY(EditAnywhere)
	UFighterStateAsset* End;
};
