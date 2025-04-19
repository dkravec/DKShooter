// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "DKShooter/DKShooterCharacter.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "../TP_WeaponComponent.h"


// Sets default values
AEnemy::AEnemy() : Super()
{
	// Set this character to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 600.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	
	Health = 100;
	PrimaryActorTick.bCanEverTick = false;

	// Set up pawn sensing
	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>("Pawn Sensing");
	PawnSensing->SightRadius = 2800.0f;
	PawnSensing->SensingInterval = 1.0f;
	PawnSensing->SetPeripheralVisionAngle(180.0f);
	PawnSensing->OnSeePawn.AddDynamic(this, &AEnemy::OnPawnSeen);

	// Set up collision
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlapBegin);
}

void AEnemy::TakeDamage(int DamageAmount)
{
	Health -= DamageAmount;
	
	if (Health <= 0)
	{
		Die();
	}
}

void AEnemy::Die()
{
	// Disable movement and collision
	GetCharacterMovement()->DisableMovement();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	// Clear collision cooldown timer
	GetWorld()->GetTimerManager().ClearTimer(CollisionCooldownTimer);
	
	SetLifeSpan(0.2f);
}

void AEnemy::OnPawnSeen(APawn* SeenPawn) 
{
	ADKShooterCharacter* Character = Cast<ADKShooterCharacter>(SeenPawn);
	if (Character) 
	{
		TargetPlayer = Character;
		if (AAIController* AIController = Cast<AAIController>(GetController()))
		{
			// Set the destination to be right in front of the player
			FVector PlayerLocation = Character->GetActorLocation();
			FVector PlayerForward = Character->GetActorForwardVector();
			FVector Destination = PlayerLocation + (PlayerForward * 100.0f); // Move to 100 units in front of player
			
			AIController->MoveToLocation(Destination, -1.0f, false, true, false, false, nullptr, true);
		}
	}
}

void AEnemy::SetHealthBasedOnWave(int WaveNumber)
{
	Health = 100 + (WaveNumber - 1) * 25;
}

void AEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bCanDealCollisionDamage)
	{
		if (ADKShooterCharacter* Player = Cast<ADKShooterCharacter>(OtherActor))
		{
			UE_LOG(LogTemp, Warning, TEXT("Enemy collided with player!"));
			Player->TakeDamage(CollisionDamage);
			
			// Start cooldown timer
			bCanDealCollisionDamage = false;
			GetWorld()->GetTimerManager().SetTimer(CollisionCooldownTimer, [this]() {
				bCanDealCollisionDamage = true;
			}, CollisionCooldown, false);
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

