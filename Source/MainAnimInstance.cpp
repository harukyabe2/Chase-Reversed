// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"
#include "MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UMainAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UMainAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	// Pawnが存在しなければ終了
	APawn* OwnerPawn = TryGetPawnOwner();
	if (!OwnerPawn) return;

	// 水平方向の速度を計算
	FVector Velocity = OwnerPawn->GetVelocity();
	GroundSpeed = UKismetMathLibrary::VSizeXY(Velocity);

	// 落下方向の速度を計算
	VerticalSpeed = Velocity.Z;

	if (ACharacter* CharacterOwner = Cast<ACharacter>(OwnerPawn))
	{
		if (UCharacterMovementComponent* MovementComponent = CharacterOwner->GetCharacterMovement())
		{
			// 空中にいるかどうかの判定
			bIsFalling = MovementComponent->IsFalling();
		}
	}
}
