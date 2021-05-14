// Fill out your copyright notice in the Description page of Project Settings.


#include "GASIntro/Gameplay/BaseAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

UBaseAttributeSet::UBaseAttributeSet():
	Attack(0.0f),
	Armor(1.0f),
	Health(100.0f),
	MaxHealth(100.0f),
	Mana(100.0f),
	MaxMana(100.0f),
	Strength(100.0f),
	MaxStrength(100.0f)
{

}

void UBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if(Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UBaseAttributeSet::StaticClass(),GET_MEMBER_NAME_CHECKED(UBaseAttributeSet,Health)))
	{
		Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.0f, MaxHealth.GetCurrentValue()));
		Health.SetBaseValue(FMath::Clamp(Health.GetBaseValue(), 0.0f, MaxHealth.GetBaseValue()));
		OnHealthChange.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue());
	}

	if(Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UBaseAttributeSet::StaticClass(),GET_MEMBER_NAME_CHECKED(UBaseAttributeSet,Mana)))
	{
		Mana.SetCurrentValue(FMath::Clamp(Mana.GetCurrentValue(), 0.0f, MaxMana.GetCurrentValue()));
		Mana.SetBaseValue(FMath::Clamp(Mana.GetBaseValue(), 0.0f, MaxMana.GetBaseValue()));
		OnManaChange.Broadcast(Mana.GetCurrentValue(), MaxMana.GetCurrentValue());
	}

	if(Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UBaseAttributeSet::StaticClass(),GET_MEMBER_NAME_CHECKED(UBaseAttributeSet,Strength)))
	{
		Strength.SetCurrentValue(FMath::Clamp(Strength.GetCurrentValue(), 0.0f, MaxStrength.GetCurrentValue()));
		Strength.SetBaseValue(FMath::Clamp(Strength.GetBaseValue(), 0.0f, MaxStrength.GetBaseValue()));
		OnStrengthChange.Broadcast(Strength.GetCurrentValue(), MaxStrength.GetCurrentValue());
	}
}
