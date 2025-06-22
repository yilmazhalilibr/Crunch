// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CCharacter.h"
#include "GAS/CAbilitySystemComponent.h"
#include "GAS/CAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "Components/WidgetComponent.h"
#include "Widgets/OverHeadStatsGauge.h"
#include <Kismet/GameplayStatics.h>
#include "GAS/CAbilitySystemStatics.h"

// Sets default values
ACCharacter::ACCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Create Ability System Component
	CAbilitySystemComponent = CreateDefaultSubobject<UCAbilitySystemComponent>(TEXT("CAbility System Component"));
	CAttributeSet = CreateDefaultSubobject<UCAttributeSet>(TEXT("CAttribute Set"));

	OverHeadWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverHead Widget Component"));
	OverHeadWidgetComponent->SetupAttachment(GetRootComponent());

	BindGASChangeDelegates();

}

void ACCharacter::ServerSideInit()
{
	CAbilitySystemComponent->InitAbilityActorInfo(this, this);
	CAbilitySystemComponent->ApplyInitialEffects();
	CAbilitySystemComponent->GiveInitialAbilities();

}

void ACCharacter::ClientSideInit()
{
	CAbilitySystemComponent->InitAbilityActorInfo(this, this);

}

bool ACCharacter::IsLocallyControlledByPlayer()
{
	return GetController() && GetController()->IsLocalPlayerController();
}

void ACCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (NewController && !NewController->IsPlayerController())
	{
		ServerSideInit();
	}

}

void ACCharacter::BeginPlay()
{
	Super::BeginPlay();

	ConfigureOverHeadStatusWidget();
}


UAbilitySystemComponent* ACCharacter::GetAbilitySystemComponent() const
{
	return CAbilitySystemComponent;
}

void ACCharacter::BindGASChangeDelegates()
{
	if (CAbilitySystemComponent)
	{
		CAbilitySystemComponent->RegisterGameplayTagEvent(UCAbilitySystemStatics::GetDeadStatTag()).AddUObject(this,&ACCharacter::DeathTagUpdated);
	}
}

void ACCharacter::DeathTagUpdated(const FGameplayTag Tag, int32 NewCount)
{
	if (NewCount != 0)
	{
		StartDeathSequence();
	}
	else
	{
		Respawn();
	}
}



void ACCharacter::ConfigureOverHeadStatusWidget()
{
	if (!OverHeadWidgetComponent)
	{
		return;
	}

	if (IsLocallyControlledByPlayer())
	{
		OverHeadWidgetComponent->SetHiddenInGame(true);
		return;

	}

	UOverHeadStatsGauge* OverHeadStatsGauge = Cast<UOverHeadStatsGauge>(OverHeadWidgetComponent->GetUserWidgetObject());
	if (OverHeadStatsGauge)
	{
		OverHeadStatsGauge->ConfigureWithASC(GetAbilitySystemComponent());
		OverHeadWidgetComponent->SetHiddenInGame(false);
		GetWorldTimerManager().ClearTimer(HeadStatGaugeVisibilityUpdateTimerHandle);
		GetWorldTimerManager().SetTimer(HeadStatGaugeVisibilityUpdateTimerHandle, this, &ACCharacter::UpdateHeadGaugeVisibility, HeadStatGaugeVisibilityCheckUpdateGap, true);
	}


}

void ACCharacter::UpdateHeadGaugeVisibility()
{
	APawn* LocalPlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (LocalPlayerPawn)
	{
		float DistSquared = FVector::DistSquared(GetActorLocation(), LocalPlayerPawn->GetActorLocation());
		OverHeadWidgetComponent->SetHiddenInGame(DistSquared > HeadStatGaugeVisibilityRangeSquared);
	}

}

void ACCharacter::StartDeathSequence()
{
	//GEgine with LOG add
	UE_LOG(LogTemp, Warning, TEXT("Character is dead!"));
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Character is dead!"));
	}
}

void ACCharacter::Respawn()
{
	UE_LOG(LogTemp, Warning, TEXT("Character is respawn!"));
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Character is respawn!"));
	}
}

 