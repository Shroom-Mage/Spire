// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FighterInnateAsset.generated.h"

class UFighterAttackAsset;

/**
 * 
 */
UCLASS()
class FIGHTER_API UFighterInnateAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	// When moving forward on the ground, GroundSpeed will be the fighter's horizontal target speed.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float GroundSpeed;
	// When below the target speed on the ground, the fighter will accelerate at GroundAcceleration per second.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float GroundAcceleration;
	// When above the target speed on the ground, the fighter will decelerate at GroundDeceleration per second.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float GroundDeceleration;
	// When moving forward in the air, AirSpeed will be the fighter's horizontal target speed.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float AirSpeed;
	// When below the target speed in the air, the fighter will accelerate at AirAcceleration per second.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float AirAcceleration;
	// When below the target speed in the air, the fighter will decelerate at AirDeceleration per second.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float AirDeceleration;
	// When the fighter jumps, the fighter's upward velocity is set to JumpVelocity.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float JumpVelocity;
	// When in the air, FallVelocity will be the fighter's vertical target speed.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float FallVelocity;
	// When ascending and above FallVelocity, the fighter will decelerate at GravityUp per second.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float GravityUp;
	// When descending and above FallVelocity, the fighter will decelerate at GravityDown per second.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float GravityDown;

	// When Passive Ground Neutral is entered, GroundNeutralAnimation will play until the state ends.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	UAnimSequence* GroundNeutralAnimation;
	// When Passive Ground Forward is entered, GroundForwardAnimation will play until the state ends.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	UAnimSequence* GroundForwardAnimation;
	// When Passive Ground Crouching is entered, GroundCrouchingAnimation will play until the state ends.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	UAnimSequence* GroundCrouchingAnimation;
	// When Passive Air Neutral is entered, AirNeutralAnimation will play until the state ends.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	UAnimSequence* AirNeutralAnimation;
	// When Passive Air Forward is entered, AirForwardAnimation will play until the state ends.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	UAnimSequence* AirForwardAnimation;
	// When Passive Air Crouching is entered, AirCrouchingAnimation will play until the state ends.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	UAnimSequence* AirCrouchingAnimation;
	// When Passive Evade Neutral is entered, EvadeNeutralAnimation will play until the state ends.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	UAnimSequence* EvadeNeutralAnimation;
	// When Passive Evade Forward is entered, EvadeForwardAnimation will play until the state ends.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	UAnimSequence* EvadeForwardAnimation;
	// When Passive Evade Crouching is entered, EvadeCrouchingAnimation will play until the state ends.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	UAnimSequence* EvadeCrouchingAnimation;

	// When Passive Ground Neutral is entered, GroundNeutralAttack will play until the state ends.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attack")
	UFighterAttackAsset* GroundNeutralAttack;
	// When Passive Ground Forward is entered, GroundForwardAttack will play until the state ends.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attack")
	UFighterAttackAsset* GroundForwardAttack;
	// When Passive Ground Crouching is entered, GroundCrouchingAttack will play until the state ends.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attack")
	UFighterAttackAsset* GroundCrouchingAttack;
	// When Passive Air Neutral is entered, AirNeutralAttack will play until the state ends.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attack")
	UFighterAttackAsset* AirNeutralAttack;
	// When Passive Air Forward is entered, AirForwardAttack will play until the state ends.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attack")
	UFighterAttackAsset* AirForwardAttack;
	// When Passive Air Crouching is entered, AirCrouchingAttack will play until the state ends.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attack")
	UFighterAttackAsset* AirCrouchingAttack;
	// When Passive Evade Neutral is entered, EvadeNeutralAttack will play until the state ends.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attack")
	UFighterAttackAsset* EvadeNeutralAttack;
	// When Passive Evade Forward is entered, EvadeForwardAttack will play until the state ends.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attack")
	UFighterAttackAsset* EvadeForwardAttack;
	// When Passive Evade Crouching is entered, EvadeCrouchingAttack will play until the state ends.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attack")
	UFighterAttackAsset* EvadeCrouchingAttack;
};
