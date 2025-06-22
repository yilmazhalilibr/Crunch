// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CGameplayAbilityTypes.h"
#include "GameplayEffectTypes.h"
#include "CAbilitySystemComponent.generated.h"

/**
 *
 */
UCLASS()
class UCAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UCAbilitySystemComponent();
	void ApplyInitialEffects();
	void GiveInitialAbilities();

private:
	void HealthUpdated(const FOnAttributeChangeData& ChangeData);

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TSubclassOf<UGameplayEffect> DeathEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TArray<TSubclassOf<UGameplayEffect>> InitialEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Ability")
	TMap<ECAbilityInputID, TSubclassOf<UGameplayAbility>> Abilities;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Ability")
	TMap<ECAbilityInputID, TSubclassOf<UGameplayAbility>> BasicAbilities;
};
