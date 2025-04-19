// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "DKShooter/DKShooterCharacter.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AEnemy::AEnemy() : Super()
{
	// Set this character to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 600.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	
	Health = 100;
	PrimaryActorTick.bCanEverTick = false;

	// Set up pawn sensing
	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>("Pawn Sensing");
	PawnSensing->SightRadius = 2800.0f;
	PawnSensing->SensingInterval = 1.0f;
	PawnSensing->SetPeripheralVisionAngle(180.0f);
	PawnSensing->OnSeePawn.AddDynamic(this, &AEnemy::OnPawnSeen);
}

void AEnemy::OnPawnSeen(APawn* SeenPawn) 
{
	ADKShooterCharacter* Character = Cast<ADKShooterCharacter>(SeenPawn);
	if (Character) 
	{
		if (AAIController* AIController = Cast<AAIController>(GetController()))
		{
			AIController->MoveToActor(Character);
		}
	}
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	// Ensure we have an AI controller
	if (!GetController())
	{
		AAIController* AIController = GetWorld()->SpawnActor<AAIController>(AAIController::StaticClass());
		AIController->Possess(this);
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

