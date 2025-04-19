// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class DKSHOOTER_API AEnemy : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

	UPROPERTY(EditAnywhere, Category = "Enemy Sense")
	class UPawnSensingComponent* PawnSensing;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	int Health;

	UFUNCTION()
	void TakeDamage(int DamageAmount);

	UFUNCTION()
	void Die();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);
};
