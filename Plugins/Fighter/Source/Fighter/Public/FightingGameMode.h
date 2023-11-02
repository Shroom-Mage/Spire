// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FightingGameMode.generated.h"

class AFighterPawn;
class UFightingComponent;
	
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAwardPointSignature, UFightingComponent*, Recipient);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRoundStartSignature);

/**
 * 
 */
UCLASS()
class FIGHTER_API AFightingGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFightingGameMode();

	UFUNCTION(BlueprintCallable, Category="Scoring")
	int GetScore(AFighterPawn* FightingComp);
	UFUNCTION(BlueprintCallable, Category="Scoring")
	int GetRound();

protected:
	virtual void BeginPlay() override;

private:
	void AddPoint(AFighterPawn* Recipient);
	UFUNCTION()
	void AddPoint(UFightingComponent* Recipient);

	void ResetPositions();

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Position")
	double StartingPosition0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Position")
	double StartingPosition1;

	UPROPERTY(BlueprintAssignable, Category="Scoring")
	FAwardPointSignature OnAwardPoint;

	UPROPERTY(BlueprintAssignable, Category="Scoring")
	FRoundStartSignature OnRoundStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Scoring")
	AFighterPawn* Fighter0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Scoring")
	AFighterPawn* Fighter1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Scoring")
	int Score0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Scoring")
	int Score1;
};
