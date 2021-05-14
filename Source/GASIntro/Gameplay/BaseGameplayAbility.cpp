// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameplayAbility.h"

FGameplayAbilityInfo::FGameplayAbilityInfo():
	CoolDown(0),
	Cost(0),
	CostType(ECostType::Mana),
	IconMaterial(nullptr),
	AbilityClass(nullptr)
{
}

FGameplayAbilityInfo::FGameplayAbilityInfo(float CoolDown, float Cost, ECostType CostType, UMaterialInstance* IconMaterial, TSubclassOf<UBaseGameplayAbility> AbilityClass):
	CoolDown(CoolDown),
	Cost(Cost),
	CostType(CostType),
	IconMaterial(IconMaterial),
	AbilityClass(AbilityClass)
{
}

FGameplayAbilityInfo UBaseGameplayAbility::GetAbilityInfo()
{
	UGameplayEffect* CooldownEffect = GetCooldownGameplayEffect();
	UGameplayEffect* CostEffect = GetCostGameplayEffect();

	float Cooldown = 0;
	float Cost = 0;
	ECostType CostType = ECostType::Mana;

	if (CooldownEffect && CostEffect)
	{
		CooldownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(1, Cooldown);

		if (CostEffect->Modifiers.Num() > 0)
		{
			FGameplayModifierInfo CostEffectModifierInfo = CostEffect->Modifiers[0];
			CostEffectModifierInfo.ModifierMagnitude.GetStaticMagnitudeIfPossible(1, Cost);

			FGameplayAttribute CostAttribute = CostEffectModifierInfo.Attribute;
			FString CostAttributeName = CostAttribute.AttributeName;
			if (CostAttributeName == "Health")
			{
				CostType = ECostType::Health;
			}

			if (CostAttributeName == "Mana")
			{
				CostType = ECostType::Mana;
			}

			if (CostAttributeName == "Strength")
			{
				CostType = ECostType::Strength;
			}
		}
		return FGameplayAbilityInfo(Cooldown, Cost, CostType, IconMaterial, GetClass());
	}

	return FGameplayAbilityInfo();
}

