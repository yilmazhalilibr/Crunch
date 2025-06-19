// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/CAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/KismetMathLibrary.h>

void UCAnimInstance::NativeInitializeAnimation()
{

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	if (OwnerCharacter)
	{
		OwnerMovementComponent = OwnerCharacter->GetCharacterMovement();
	}

}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (!OwnerCharacter) return;
	if (!OwnerMovementComponent) return;

	//Lean 

	Speed = OwnerCharacter->GetVelocity().Length();
	FRotator BodyRot = OwnerCharacter->GetActorRotation();
	FRotator BodyRotDelta = UKismetMathLibrary::NormalizedDeltaRotator(BodyRot, BodyPrevRot);
	BodyPrevRot = BodyRot;

	YawSpeed = BodyRotDelta.Yaw / DeltaSeconds;
	SmoothYawSpeed = UKismetMathLibrary::FInterpTo(SmoothYawSpeed, YawSpeed, DeltaSeconds, YawSpeedSmoothLerpSpeed);

	// Jump

	bIsJumping = OwnerMovementComponent->IsFalling();

	// Look Rotation Offset

	FRotator ControlRot = OwnerCharacter->GetBaseAimRotation();
	LookRotOffset = UKismetMathLibrary::NormalizedDeltaRotator(ControlRot, BodyRot);

}

void UCAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{

}
