// Fill out your copyright notice in the Description page of Project Settings.


#include "./EnemySpawner.h"
#include "./Enemy.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::SpawnEnemy()
{
/*
	if (!IsValid(EnemyObject))
	{
		// step 3
		// check if the ring object is not currently active
		if (bIsEnemyObjectActive == false) {
			// Create spawn parameters to control the spawning process
			FActorSpawnParameters SpawnParams;
			// Set the owner of the spawned ring to be this spawner
			SpawnParams.Owner = this;

			// Set the socllison handling method for spawning the ring
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			UWorld* World = GetWorld();
			EnemyObject = World->SpawnActor<AEnemy>(EnemyBlueprint, this->GetActorLocation(), this->GetActorRotation(), SpawnParams);

			// check if the ring object wa successfully spawned
			if (EnemyObject) {
				EnemyObject->OnDestroyed.AddDynamic(this, &AEnemySpawner::OnEnemyKilled);
				// set flag indicating ring object is currently active
				bIsEnemyObjectActive = true;
			}
		}
	}*/
}

void AEnemySpawner::OnEnemyKilled(AActor* DestroyedActor) {
	bIsEnemyObjectActive = false;
	DestroyedActor->OnDestroyed.RemoveAll(this);
}