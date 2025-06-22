// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "CCharacter.generated.h"


UCLASS()
class ACCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACCharacter();


	void ServerSideInit();
	void ClientSideInit();
	bool IsLocallyControlledByPlayer();
	//Only called on the server when a player possesses this character
	virtual void PossessedBy(AController* NewController) override;


protected:

	//begin play
	virtual void BeginPlay() override;

public:


	/***********************************************/
	/* IAbilitySystemInterface Implementation */
	/***********************************************/

	// Inherited via IAbilitySystemInterface
public:

	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:
	void BindGASChangeDelegates();
	void DeathTagUpdated(const FGameplayTag Tag, int32 NewCount);

	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay Ability")
	TObjectPtr<class UCAbilitySystemComponent> CAbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<class UCAttributeSet> CAttributeSet;

	/***********************************************/
	/*                     UI                      */
	/***********************************************/

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "UI")
	TObjectPtr<class UWidgetComponent> OverHeadWidgetComponent;

	void ConfigureOverHeadStatusWidget();

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float HeadStatGaugeVisibilityCheckUpdateGap = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float HeadStatGaugeVisibilityRangeSquared = 10000000.f;

	FTimerHandle HeadStatGaugeVisibilityUpdateTimerHandle;

	void UpdateHeadGaugeVisibility();
	/***********************************************/
	/*              Death And Respawn              */
	/***********************************************/

	void StartDeathSequence();
	void Respawn();

};
