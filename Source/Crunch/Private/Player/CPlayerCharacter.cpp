// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"




// Sets default values
ACPlayerCharacter::ACPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	ViewCam = CreateDefaultSubobject<UCameraComponent>(TEXT("View Cam"));
	CameraBoom->SetupAttachment(GetRootComponent());

	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	ViewCam->SetupAttachment(CameraBoom);

	bUseControllerRotationYaw = false; // Rotate character based on controller yaw

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character will rotate to face the direction of movement
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f); // Set rotation rate for character movement

}
// Called when the game starts or when spawned
void ACPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}
// Called every frame
void ACPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
// Called to bind functionality to input
void ACPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::Jump);
		EnhancedInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::HandleLookInput);
		EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::HandleMoveInput);
	}

}
void ACPlayerCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	APlayerController* OwningPlayerController = GetController<APlayerController>();
	if (OwningPlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem = OwningPlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		if (InputSubsystem)
		{
			InputSubsystem->RemoveMappingContext(GameplayInputMappingContext);
			InputSubsystem->AddMappingContext(GameplayInputMappingContext, 0);
		}

	}



}
void ACPlayerCharacter::HandleLookInput(const FInputActionValue& Value)
{
	FVector2D InputVal = Value.Get<FVector2D>();
	AddControllerPitchInput(-InputVal.Y);
	AddControllerYawInput(InputVal.X);
}
void ACPlayerCharacter::HandleMoveInput(const FInputActionValue& Value)
{
	FVector2D InputVal = Value.Get<FVector2D>();
	InputVal.Normalize();

	AddMovementInput(GetMoveForwardDir() * InputVal.Y + GetLookRightDir() * InputVal.X);


}

FVector ACPlayerCharacter::GetLookRightDir() const
{
	if (ViewCam)
	{
		return ViewCam->GetRightVector();
	}
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(22, 5.f, FColor::Red, TEXT("ViewCam is not set!"));
	}
	return FVector::ZeroVector;
}

FVector ACPlayerCharacter::GetLookForwardDir() const
{
	return ViewCam->GetForwardVector();
}

FVector ACPlayerCharacter::GetMoveForwardDir() const
{
	return FVector::CrossProduct(GetLookRightDir(), FVector::UpVector);
}
