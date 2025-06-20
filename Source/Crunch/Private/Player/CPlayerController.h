// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

/**
 *
 */
UCLASS()
class ACPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	//Only called on the server
	void OnPossess(APawn* InPawn) override;
	// Only called on the client
	void AcknowledgePossession(APawn* InPawn) override;

private:
	void SpawnGameplayWidget();

	UPROPERTY()
	TObjectPtr<class ACPlayerCharacter> CPlayerCharacter;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UGameplayWidget> GameplayWidgetClass;
	
	UPROPERTY()
	TObjectPtr<class UGameplayWidget> GameplayWidget;

};
