// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/CAbilitySystemStatics.h"

FGameplayTag UCAbilitySystemStatics::GetBasicAttackAbilityTag()
{

	return FGameplayTag::RequestGameplayTag(FName("Ability.BasicAttack"));

}
