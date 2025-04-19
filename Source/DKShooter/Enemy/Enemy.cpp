// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "DKShooter/DKShooterCharacter.h"
#include "AIController.h"


// Sets default values
AEnemy::AEnemy() : Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USphereComponent>(TEXT("RootSphereComponent"));
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
	SetRootComponent(Root);
	//RootComponent = Root;
	VisualMesh->SetupAttachment(RootComponent);

	//STEP 2
	VisualMesh->SetCollisionProfileName(TEXT("OverlapAll"));
	SetActorEnableCollision(true);
	bGenerateOverlapEventsDuringLevelStreaming = true;
	
	Health = 100;
	PrimaryActorTick.bCanEverTick = false;


	// EnemyType = EEnemyType::ENone;
	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>("Pawn Sensing");
	PawnSensing->SightRadius = 2800.0f;
	PawnSensing->SensingInterval = 1.0f;
	PawnSensing->SetPeripheralVisionAngle(180.0f);

	//GuardState = EAIState::Idle;

	PawnSensing->OnSeePawn.AddDynamic(this, &AEnemy::OnPawnSeen);

}


void AEnemy::OnPawnSeen(APawn* SeenPawn) {
	ADKShooterCharacter* Character = Cast< ADKShooterCharacter>(SeenPawn);
	if (Character) {
		Cast<AAIController>(GetController())->MoveToActor(Character);
	}
}
// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

