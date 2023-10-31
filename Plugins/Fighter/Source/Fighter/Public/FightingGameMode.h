// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FightingGameMode.generated.h"

class UFightingComponent;
	
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFighterHitSignature, UFightingComponent*, Attacker, UFightingComponent*, Receiver);

/**
 * 
 */
UCLASS()
class FIGHTER_API AFightingGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Scoring")
	void AddPoint(UFightingComponent* Recipient);
	UFUNCTION(BlueprintCallable, Category="Scoring")
	int GetScore(UFightingComponent* Recipient);

public:
	UPROPERTY(BlueprintAssignable, Category="Combat")
	FFighterHitSignature OnFighterHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Scoring")
	UFightingComponent* Fighter0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Scoring")
	UFightingComponent* Fighter1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Scoring")
	int Score0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Scoring")
	int Score1;
};
