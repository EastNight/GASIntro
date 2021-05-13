// Fill out your copyright notice in the Description page of Project Settings.


#include "GASIntro/Gameplay/PlayerExecutionCalculation.h"
#include "GASIntro/Gameplay/BaseAttributeSet.h"


UPlayerExecutionCalculation::UPlayerExecutionCalculation()
{
	DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Attack, Target, true)
	DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Armor, Target, true)
	DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Health, Target, true)

	RelevantAttributesToCapture.Add(AttackDef);
	RelevantAttributesToCapture.Add(ArmorDef);
	RelevantAttributesToCapture.Add(HealthDef);
}

void UPlayerExecutionCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	float AttackMagnitude,ArmorMagnitude = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(AttackDef, FAggregatorEvaluateParameters(), AttackMagnitude);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(ArmorDef, FAggregatorEvaluateParameters(), ArmorMagnitude);

	float FinalDamage = FMath::Clamp(AttackMagnitude - ArmorMagnitude, 0.0f, AttackMagnitude - ArmorMagnitude);


	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HealthProperty,EGameplayModOp::Additive,-FinalDamage));
}
