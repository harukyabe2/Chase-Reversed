// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainAnimInstance.generated.h"

class AMainCharacter;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class CHASE_REVERSED_API UMainAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	// 初期化処理
	virtual void NativeInitializeAnimation() override;

	// 毎フレームの更新処理
	virtual void NativeUpdateAnimation(float DeltaTime) override;

protected:
	// キャラクターの参照
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	TObjectPtr<AMainCharacter> MainCharacter;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	TObjectPtr<UCharacterMovementComponent> MainCharacterMovement;

	// 移動速度
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float GroundSpeed;

	// 移動速度
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float VerticalSpeed;

	// 空中にいるかどうか
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool bIsFalling;
};
