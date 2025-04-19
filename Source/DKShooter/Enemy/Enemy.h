// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../TP_WeaponComponent.h"
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

	UFUNCTION()
	void SetHealthBasedOnWave(int WaveNumber);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);

private:
	ADKShooterCharacter* TargetPlayer;
	float CollisionDamage = 10.0f;
	float CollisionCooldown = 1.0f;
	FTimerHandle CollisionCooldownTimer;
	bool bCanDealCollisionDamage = true;
};
