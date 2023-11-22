// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ArcanaEffect.generated.h"

class AFightingGameMode;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class SPIRE_API UArcanaEffect : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void BeginMatch();
	UFUNCTION(BlueprintCallable)
	void StartMatch();
	
	UFUNCTION(BlueprintImplementableEvent)
	void BeginRound();
	UFUNCTION(BlueprintCallable)
	void StartRound();

	UFUNCTION(BlueprintImplementableEvent)
	void BeginPoint();
	UFUNCTION(BlueprintCallable)
	void StartPoint();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AFightingGameMode* Match;
};
