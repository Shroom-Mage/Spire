// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FightingGameMode.generated.h"

class AFighterPawn;

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

	UFUNCTION(BlueprintCallable)
	virtual void BeginMatch();

	UFUNCTION(BlueprintImplementableEvent, DisplayName="BeginMatch")
	void OnBeginMatch();

	UFUNCTION(BlueprintCallable)
	virtual void BeginRound();

	UFUNCTION(BlueprintImplementableEvent, DisplayName="BeginRound")
	void OnBeginRound();

	UFUNCTION(BlueprintCallable)
	virtual void BeginPoint();

	UFUNCTION(BlueprintImplementableEvent, DisplayName="BeginPoint")
	void OnBeginPoint();

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void AddPoint(AFighterPawn* Recipient);

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Match")
	AFighterPawn* Fighter0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Match")
	AFighterPawn* Fighter1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Match")
	int Score0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Match")
	int Score1;
};
