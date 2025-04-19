// Copyright Epic Games, Inc. All Rights Reserved.

#include "DKShooterGameMode.h"
#include "DKShooterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "./Enemy/EnemySpawner.h"

ADKShooterGameMode::ADKShooterGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}

void ADKShooterGameMode::BeginPlay() 
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawner::StaticClass(), FoundEnemies);

	SpawnEnemies();

	GetWorldTimerManager().SetTimer(WaveCheckTimer, this, &ADKShooterGameMode::CheckWaveStatus, WaveCheckInterval, true);
}

void ADKShooterGameMode::SpawnEnemies() 
{
	if (FoundEnemies.Num() > 0) 
	{
		for (AActor* Spawner : FoundEnemies)
		{
			if (AEnemySpawner* MySpawner = Cast<AEnemySpawner>(Spawner))
			{
				MySpawner->SpawnEnemy();
			}
		}
	}
}

void ADKShooterGameMode::CheckWaveStatus()
{
	bool AllEnemiesDead = true;

	// Check all spawners
	for (AActor* Spawner : FoundEnemies)
	{
		if (AEnemySpawner* MySpawner = Cast<AEnemySpawner>(Spawner))
		{
			if (MySpawner->bIsEnemyObjectActive)
			{
				AllEnemiesDead = false;
				break;
			}
		}
	}

	// If all enemies are dead, spawn next wave
	if (AllEnemiesDead)
	{
		CurrentWave++;
		SpawnEnemies();
	}
}