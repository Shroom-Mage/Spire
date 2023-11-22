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

	UFUNCTION(BlueprintCallable, Category="Match")
	int GetScore(AFighterPawn* FightingComp);

	UFUNCTION(BlueprintCallable, Category="Match")
	int GetRound();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Arcana Parameters")
	double StartingPosition0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Arcana Parameters")
	double StartingPosition1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Arcana Parameters")
	float ResourceMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Arcana Parameters")
	float ResourceMaxModifier = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Match")
	AFighterPawn* Fighter0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Match")
	AFighterPawn* Fighter1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Match")
	int Score0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Match")
	int Score1;
};
