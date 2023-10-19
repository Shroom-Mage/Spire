// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterPawn.h"
#include "FightingComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AFighterPawn::AFighterPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Fighting = CreateDefaultSubobject<UFightingComponent>(TEXT("Fighting"));

	Base = CreateDefaultSubobject<USceneComponent>(TEXT("Base"));
	Base->SetupAttachment(RootComponent);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(Base);
	Fighting->SetSkeletalMesh(SkeletalMesh);

	BodyBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BodyBox"));
	BodyBox->SetupAttachment(Base);
	BodyBox->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	BodyBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BodyBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	BodyBox->ShapeColor = FColor(0, 0, 255, 255);
	Fighting->SetBodyBox(BodyBox);

	AttackBox = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackBox"));
	AttackBox->SetupAttachment(Base);
	AttackBox->ShapeColor = FColor(255, 0, 0, 255);
	Fighting->SetAttackBox(AttackBox);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Base);
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	SpringArm->SetRelativeRotation(FRotator(-45.0, 0.0, 0.0));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void AFighterPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFighterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFighterPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//if (PlayerInputComponent) {
	//	PlayerInputComponent->BindAxis("Move", this, &AFighterPawn::Move);
	//	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AFighterPawn::Jump);
	//	PlayerInputComponent->BindAction("Evade", EInputEvent::IE_Pressed, this, &AFighterPawn::Evade);
	//	PlayerInputComponent->BindAction("Normal", EInputEvent::IE_Pressed, this, &AFighterPawn::Normal);
	//	PlayerInputComponent->BindAction("Special", EInputEvent::IE_Pressed, this, &AFighterPawn::Special);
	//}
}

void AFighterPawn::Move(float Value)
{
	Fighting->Move(Value);
}

void AFighterPawn::Jump()
{
	Fighting->Jump();
}

void AFighterPawn::Evade()
{
	Fighting->Evade();
}

void AFighterPawn::Normal()
{
	Fighting->Normal();
}

void AFighterPawn::Special()
{
	Fighting->Special();
}
