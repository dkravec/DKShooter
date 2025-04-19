// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterHUD.h"
#include "Blueprint/UserWidget.h"

AShooterHUD::AShooterHUD()
{
}

void AShooterHUD::BeginPlay()
{
	Super::BeginPlay();

	if (DKShooterHUDClass)
	{
		HUDWidget = CreateWidget<UDKShooterHUD>(GetWorld(), DKShooterHUDClass);
		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
		}
	}
}
