// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OverHeadStatsGauge.generated.h"

/**
 *
 */
UCLASS()
class UOverHeadStatsGauge : public UUserWidget
{
	GENERATED_BODY()
public:
	void ConfigureWithASC(class UAbilitySystemComponent* AbilitySystemComponent);

private:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UValueGauge> HealthBar;

	UPROPERTY(meta = (BindWidget))//mana
	TObjectPtr<class UValueGauge> ManaBar;

};
