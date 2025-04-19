// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DKShooterGameMode.generated.h"

UCLASS(minimalapi)
class ADKShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADKShooterGameMode();

	void SpawnEnemies();
	void CheckWaveStatus();

	UPROPERTY(EditAnywhere, Category = "Wave Settings")
	int CurrentWave = 1;
protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<AActor*> FoundEnemies;

	UPROPERTY(EditAnywhere, Category = "Wave Settings")
	float WaveCheckInterval = 4.0f;

	FTimerHandle WaveCheckTimer;
};



