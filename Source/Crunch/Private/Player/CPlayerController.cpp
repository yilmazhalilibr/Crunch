// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CPlayerController.h"
#include "Character/CCharacter.h"
#include "Player/CPlayerCharacter.h"
#include "Widgets/GameplayWidget.h"


void ACPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	CPlayerCharacter = Cast<ACPlayerCharacter>(InPawn);

	if (CPlayerCharacter)
	{
		CPlayerCharacter->ServerSideInit();

	}
}

void ACPlayerController::AcknowledgePossession(APawn* InPawn)
{
	Super::AcknowledgePossession(InPawn);
	CPlayerCharacter = Cast<ACPlayerCharacter>(InPawn);
	if (CPlayerCharacter)
	{
		CPlayerCharacter->ClientSideInit();
		SpawnGameplayWidget();
	}
}

void ACPlayerController::SpawnGameplayWidget()
{
	if (!IsLocalPlayerController()) return;


	GameplayWidget = CreateWidget<UGameplayWidget>(this, GameplayWidgetClass);
	if (GameplayWidget)
	{
		GameplayWidget->AddToViewport();
	}

}
