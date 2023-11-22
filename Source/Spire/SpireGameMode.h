// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FightingGameMode.h"
#include "ArcanaAsset.h"
#include "SpireGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SPIRE_API ASpireGameMode : public AFightingGameMode
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Arcana")
	TArray<UArcanaAsset*> ArcanaDeck;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Arcana")
	TArray<UArcanaAsset*> ActiveArcana;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Arcana")
	TArray<UArcanaEffect*> ActiveEffects;
};
