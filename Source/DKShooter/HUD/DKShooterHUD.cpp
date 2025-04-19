// Fill out your copyright notice in the Description page of Project Settings.

#include "DKShooterHUD.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "../Enemy/Enemy.h"
#include "Kismet/GameplayStatics.h"
#include <DKShooter/DKShooterGameMode.h>
#include <DKShooter/DKShooterCharacter.h>

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

    if (PlayerHealthText)
    {
        PlayerHealthText->TextDelegate.BindUFunction(this, "SetPlayerHealthText");
    }

    if (RestartButton)
    {
        RestartButton->OnClicked.AddDynamic(this, &UDKShooterHUD::OnRestartButtonClicked);
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

FText UDKShooterHUD::SetPlayerHealthText()
{
    if (ADKShooterCharacter* Player = Cast<ADKShooterCharacter>(GetOwningPlayerPawn()))
    {
        return FText::FromString(FString::Printf(TEXT("Player Health: %d/%d"), Player->CurrentHealth, Player->MaxHealth));
    }
    return FText::FromString("Player Health: 0/0");
}

void UDKShooterHUD::OnRestartButtonClicked()
{
    // Reset the game mode
    if (ADKShooterGameMode* GameMode = Cast<ADKShooterGameMode>(GetWorld()->GetAuthGameMode()))
    {
        GameMode->CurrentWave = 1;
        GameMode->SpawnEnemies();
    }

    // Reset player health and movement
    if (ADKShooterCharacter* Player = Cast<ADKShooterCharacter>(GetOwningPlayerPawn()))
    {
        Player->CurrentHealth = Player->MaxHealth;
        
        if (APlayerController* PC = Cast<APlayerController>(Player->GetController()))
        {
            PC->SetInputMode(FInputModeGameOnly());
            PC->SetIgnoreMoveInput(false);
            PC->SetIgnoreLookInput(false);
            PC->bShowMouseCursor = false;
            PC->bEnableClickEvents = false;
            PC->bEnableMouseOverEvents = false;
        }
    }
}

