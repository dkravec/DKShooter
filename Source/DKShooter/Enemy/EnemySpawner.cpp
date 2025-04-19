// Fill out your copyright notice in the Description page of Project Settings.


#include "./EnemySpawner.h"
#include "./Enemy.h"
#include "../DKShooterGameMode.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	// Start the first spawn
	SpawnEnemy();
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::SpawnEnemy()
{
	if (!bIsEnemyObjectActive && EnemyBlueprint)
	{
		// Clear any existing timer
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
		
		// Spawn the enemy
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = GetActorRotation();
		EnemyObject = GetWorld()->SpawnActor<AEnemy>(EnemyBlueprint, SpawnLocation, SpawnRotation);
		
		if (EnemyObject)
		{
			bIsEnemyObjectActive = true;
			EnemyObject->OnDestroyed.AddDynamic(this, &AEnemySpawner::OnEnemyKilled);
		}
	}
}

void AEnemySpawner::OnEnemyKilled(AActor* DestroyedActor)
{
	bIsEnemyObjectActive = false;
	
	// Calculate new spawn delays for increased difficulty
	SpawnDelayRangeLow = SpawnDelayRangeLow / DifficultyScalar;
	SpawnDelayRangeHigh = SpawnDelayRangeHigh / DifficultyScalar;
	
	// Calculate new spawn delay
	CurrentSpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
	
	// Set timer for next spawn
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AEnemySpawner::SpawnEnemy, CurrentSpawnDelay, false);
}