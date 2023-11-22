// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FightingGameMode.generated.h"

class AFighterPawn;
class UFightingComponent;

/**
 * 
 */
UCLASS()
class FIGHTER_API AFightingGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFightingGameMode();

private:
	void ResetPositions();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void BeginMatch();

	UFUNCTION(BlueprintImplementableEvent)
	void BeginRound();

	UFUNCTION(BlueprintImplementableEvent)
	void BeginPoint();

	UFUNCTION()
	void AddPoint(AFighterPawn* Recipient);
	void AddPoint(UFightingComponent* Recipient);

	UFUNCTION(BlueprintCallable, Category="Scoring")
	int GetScore(AFighterPawn* FightingComp);

	UFUNCTION(BlueprintCallable, Category="Scoring")
	int GetRound();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aspect")
	double StartingPosition0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aspect")
	double StartingPosition1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aspect")
	float ResourceMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aspect")
	float ResourceMaxModifier = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Scoring")
	AFighterPawn* Fighter0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Scoring")
	AFighterPawn* Fighter1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Scoring")
	int Score0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Scoring")
	int Score1;
};
