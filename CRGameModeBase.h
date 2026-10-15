// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CRGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CHASE_REVERSED_API ACRGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ACRGameModeBase();
	
protected:
	virtual void StartPlay() override;

	// 制限時間
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Rules")
	float TimeLimit;

	// 残り時間
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Rules")
	float RemainingTime;

	// カウントダウンタイマー
	FTimerHandle CountdownTimer;

	// カウントダウン関数
	void CountdownTick();

	// 時間切れ処理
	void HandleGameOver();

	// 時間切れでUIへ通知
	UFUNCTION(BlueprintImplementableEvent, Category = "Game Rules")
	void OnGameOver();

public:
	// 残り時間の取得
	UFUNCTION(BlueprintCallable, Category = "Game Rules")
	float GetRemainingTime() const { return RemainingTime; };
};
