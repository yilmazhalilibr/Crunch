// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ValueGauge.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UValueGauge::NativePreConstruct()
{
	Super::NativePreConstruct();

	ProgressBar->SetFillColorAndOpacity(BarColor);



}

void UValueGauge::SetAndBoundGameplayAttribute(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayAttribute& Attribute, const FGameplayAttribute& MaxAttribute)
{
	if (AbilitySystemComponent)
	{
		bool bFound;
		float Value = AbilitySystemComponent->GetGameplayAttributeValue(Attribute, bFound);
		float MaxValue = AbilitySystemComponent->GetGameplayAttributeValue(MaxAttribute, bFound);
		if (bFound)
		{
			SetValue(Value, MaxValue);
		}

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(this, &UValueGauge::ValueChange);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MaxAttribute).AddUObject(this, &UValueGauge::MaxValueChange);

	}
}

void UValueGauge::SetValue(float NewValue, float NewMaxValue)
{

	CachedValue = NewValue;
	CachedMaxValue = NewMaxValue;

	if (NewMaxValue == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("ValueGauge: NewMaxValue is zero, cannot set value."));
		return;
	}

	float NewPercent = NewValue / NewMaxValue;
	ProgressBar->SetPercent(NewPercent);

	FNumberFormattingOptions FormatOpt = FNumberFormattingOptions().SetMinimumFractionalDigits(0);

	ValueText->SetText(FText::Format(FTextFormat::FromString("{0}/{1}"),
		FText::AsNumber(NewValue, &FormatOpt),
		FText::AsNumber(NewMaxValue, &FormatOpt)));

}

void UValueGauge::ValueChange(const FOnAttributeChangeData& Data)
{
	SetValue(Data.NewValue, CachedValue);
}

void UValueGauge::MaxValueChange(const FOnAttributeChangeData& Data)
{
	SetValue(CachedMaxValue, Data.NewValue);
}
