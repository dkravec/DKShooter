// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class DKSHOOTER_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnEnemyKilled(AActor* DestroyedActor);
public:	

	UFUNCTION()
	void SpawnEnemy();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "ClassToSpawn")
	UClass* EnemyBlueprint;

	UPROPERTY(Transient)
	class AEnemy* EnemyObject;

	UPROPERTY(Transient)
	bool bIsEnemyObjectActive = false;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	float SpawnDelayRangeLow = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	float SpawnDelayRangeHigh = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	float DifficultyScalar = 1.1f;

private:
	FTimerHandle SpawnTimerHandle;
	float CurrentSpawnDelay;
};
