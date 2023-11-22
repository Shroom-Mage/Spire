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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Arcana")
	UArcanaAsset* ArcanaActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Arcana")
	UArcanaAsset* ArcanaDeck;
};
