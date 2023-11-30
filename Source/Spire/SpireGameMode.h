// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FightingGameMode.h"
#include "SpireGameMode.generated.h"

class UArcanaAsset;
class UArcanaEffect;

/**
 * 
 */
UCLASS()
class SPIRE_API ASpireGameMode : public AFightingGameMode
{
	GENERATED_BODY()
	
private:
	void DrawCard();

protected:
	virtual void BeginMatch() override;

	virtual void BeginRound() override;

	virtual void BeginPoint() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Arcana")
	TArray<UArcanaAsset*> ArcanaDeck;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Arcana")
	TArray<UArcanaAsset*> ActiveArcana;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Arcana")
	TArray<UArcanaEffect*> ActiveEffects;
};
