// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/CAbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "GameplayAbilitySpec.h"
#include "GAS/CAttributeSet.h"

UCAbilitySystemComponent::UCAbilitySystemComponent()
{
	GetGameplayAttributeValueChangeDelegate(UCAttributeSet::GetHealthAttribute()).AddUObject(this, &UCAbilitySystemComponent::HealthUpdated);
}

void UCAbilitySystemComponent::ApplyInitialEffects()
{
	if (!GetOwner() || !GetOwner()->HasAuthority()) return;



	for (const TSubclassOf<UGameplayEffect>& EffectClass : InitialEffect)
	{
		if (EffectClass)
		{
			FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingSpec(EffectClass, 1.0f, MakeEffectContext());
			ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

		}
	}
}

void UCAbilitySystemComponent::GiveInitialAbilities()
{
	if (!GetOwner() || !GetOwner()->HasAuthority()) return;


	for (const TPair< ECAbilityInputID, TSubclassOf<UGameplayAbility>>& AbilityPair : Abilities)
	{
		GiveAbility(FGameplayAbilitySpec(AbilityPair.Value, 0, (int32)AbilityPair.Key, this));
	}
	for (const TPair< ECAbilityInputID, TSubclassOf<UGameplayAbility>>& AbilityPair : BasicAbilities)
	{
		GiveAbility(FGameplayAbilitySpec(AbilityPair.Value, 1, (int32)AbilityPair.Key, this));
	}
}

void UCAbilitySystemComponent::HealthUpdated(const FOnAttributeChangeData& ChangeData)
{
	if (!GetOwner()) return;

	if (ChangeData.NewValue <= 0 && GetOwner()->HasAuthority() && DeathEffect)
	{
		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingSpec(DeathEffect, 1.0f, MakeEffectContext());
		ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	}

}
