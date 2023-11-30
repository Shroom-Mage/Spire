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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AFightingGameMode* Match;
};
