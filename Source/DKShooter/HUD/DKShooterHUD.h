// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DKShooterHUD.generated.h"


UCLASS()
class DKSHOOTER_API UDKShooterHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/* TextBlock for current wave */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* WaveText;

	/* TextBlock for total enemy health */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* EnemyHealthText;

	/* TextBlock for player health */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* PlayerHealthText;

	/* Binds text blocks to functions to set text */
	virtual bool Initialize() override;

	/* Callback to set the wave text */
	UFUNCTION()
	FText SetWaveText();

	/* Callback to set the enemy health text */
	UFUNCTION()
	FText SetEnemyHealthText();

	/* Callback to set the player health text */
	UFUNCTION()
	FText SetPlayerHealthText();
};
