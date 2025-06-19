// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"

#include "CPlayerCharacter.generated.h"

// Forward declarations
class UInputAction;
class UInputMappingContext;
class UEnhancedInputComponent; // Uncomment if using Enhanced Input System
class USpringArmComponent;
class UCameraComponent;



UCLASS()
class ACPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPlayerCharacter();


	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	TObjectPtr<class USpringArmComponent> CameraBoom;
	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	TObjectPtr<class UCameraComponent> ViewCam;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> JumpInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> LookInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> GameplayInputMappingContext;


	void HandleLookInput(const FInputActionValue& Value);
	void HandleMoveInput(const FInputActionValue& Value);

	FVector GetLookRightDir() const;
	FVector GetLookForwardDir() const;
	FVector GetMoveForwardDir() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PawnClientRestart() override;

};
