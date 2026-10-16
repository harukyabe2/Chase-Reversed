// Fill out your copyright notice in the Description page of Project Settings.


#include "CRGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

ACRGameModeBase::ACRGameModeBase()
{
	TimeLimit = 60.0f;
}

void ACRGameModeBase::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	RemainingTime = TimeLimit;

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);

	if (PC)
	{
		// 入力モードを戻す
		FInputModeGameOnly InputMode;
		PC->SetInputMode(InputMode);

		// マウスカーソルを非表示する
		PC->bShowMouseCursor = false;

		// 移動・視点入力を有効化
		PC->SetIgnoreMoveInput(false);
		PC->SetIgnoreLookInput(false);

		// キャラクターの入力受付を開始
		if (APawn* PlayerPawn = PC->GetPawn())
		{
			PlayerPawn->EnableInput(PC);
		}
	}

	GetWorldTimerManager().SetTimer(CountdownTimer, this, &ACRGameModeBase::CountdownTick, 1.0f, true);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Debug message: CRGameMode is used."));
}

void ACRGameModeBase::CountdownTick()
{
	RemainingTime -= 1.0f;

	if (RemainingTime <= 0.0f)
	{
		RemainingTime = 0.0f;

		// タイマーを止める
		GetWorldTimerManager().ClearTimer(CountdownTimer);

		HandleGameOver();
	}
}

void ACRGameModeBase::HandleGameOver()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);

	if (PC)
	{
		// 入力受付を停止
		PC->SetIgnoreMoveInput(true);
		PC->SetIgnoreLookInput(true);

		// プレイヤーの移動を停止
		if (ACharacter* PlayerCharacter = Cast<ACharacter>(PC->GetPawn()))
		{
			if (UCharacterMovementComponent* MovementComp = PlayerCharacter->GetCharacterMovement())
			{
				MovementComp->ConsumeInputVector();

				if (MovementComp->IsFalling())
				{
					MovementComp->Velocity.X = 0.0f;
					MovementComp->Velocity.Y = 0.0f;
				}
				else
				{
					MovementComp->StopMovementImmediately();
				}
			}
		}
		// マウスカーソルを表示する
		PC->bShowMouseCursor = true;

		// 入力モードをUI専用にする
		FInputModeUIOnly InputMode;
		PC->SetInputMode(InputMode);
	}

	OnGameOver();
}

