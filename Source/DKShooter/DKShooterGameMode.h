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
protected:
	virtual void BeginPlay() override;

	TArray<AActor*> FoundEnemies;
};



