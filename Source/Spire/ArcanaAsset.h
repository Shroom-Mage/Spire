// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ArcanaEffect.h"
#include "ArcanaAsset.generated.h"

/**
 * 
 */
UCLASS()
class SPIRE_API UArcanaAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName Name;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* Texture;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UArcanaEffect> Effect;
};
