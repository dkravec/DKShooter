// Fill out your copyright notice in the Description page of Project Settings.

#include "DKShooterHUD.h"
#include "Components/TextBlock.h"
#include "../DKShooterGameMode.h"
#include "../Enemy/Enemy.h"
#include "Kismet/GameplayStatics.h"
#include <DKShooter/DKShooterGameMode.h>

bool UDKShooterHUD::Initialize()
{
    bool Success = Super::Initialize();

    if (WaveText)
    {
        WaveText->TextDelegate.BindUFunction(this, "SetWaveText");
    }

    if (EnemyHealthText)
    {
        EnemyHealthText->TextDelegate.BindUFunction(this, "SetEnemyHealthText");
    }

    return Success;
}

FText UDKShooterHUD::SetWaveText()
{
    if (ADKShooterGameMode* GameMode = Cast<ADKShooterGameMode>(GetWorld()->GetAuthGameMode()))
    {
        return FText::FromString(FString::Printf(TEXT("Wave: %d"), GameMode->CurrentWave));
    }
    return FText::FromString("Wave: 0");
}

FText UDKShooterHUD::SetEnemyHealthText()
{
    int32 TotalHealth = 0;
    TArray<AActor*> FoundEnemies;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), FoundEnemies);

    for (AActor* Actor : FoundEnemies)
    {
        if (AEnemy* Enemy = Cast<AEnemy>(Actor))
        {
            TotalHealth += Enemy->Health;
        }
    }

    return FText::FromString(FString::Printf(TEXT("Enemy Health: %d"), TotalHealth));
}

