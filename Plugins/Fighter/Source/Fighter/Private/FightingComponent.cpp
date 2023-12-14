// Fill out your copyright notice in the Description page of Project Settings.


#include "FightingComponent.h"
#include "FightingGameMode.h"
#include "FighterPawn.h"

// Sets default values for this component's properties
UFightingComponent::UFightingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UFightingComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UFightingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

//void UFightingComponent::OnAttackOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("Component OverlapBegin")));
//	if (OtherComp->GetFName() == TEXT("BodyBox")) {
//		AFighterPawn* OtherFighter = Cast<AFighterPawn>(OtherActor);
//		if (OtherFighter != OwnerFighter)
//			OwnerFighter->Target = OtherFighter;
//	}
//}
//
//void UFightingComponent::OnAttackOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("Component OverlapEnd")));
//	if (OtherComp->GetFName() == TEXT("BodyBox")) {
//		AFighterPawn* OtherFighter = Cast<AFighterPawn>(OtherActor);
//		if (OtherFighter == OwnerFighter->Target)
//			OwnerFighter->Target = nullptr;
//	}
//}

void UFightingComponent::SetOwnerFighter(AFighterPawn* Fighter)
{
	OwnerFighter = Fighter;
}
