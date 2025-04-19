// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DKShooterHUD.h"
#include "ShooterHUD.generated.h"

UCLASS()
class DKSHOOTER_API AShooterHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AShooterHUD();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "HUD")
	TSubclassOf<UDKShooterHUD> DKShooterHUDClass;

	UPROPERTY()
	UDKShooterHUD* HUDWidget;
};
