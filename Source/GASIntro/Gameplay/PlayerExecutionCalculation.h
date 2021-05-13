// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "PlayerExecutionCalculation.generated.h"

/**
 * 
 */
UCLASS()
class GASINTRO_API UPlayerExecutionCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:
	UPlayerExecutionCalculation();

	DECLARE_ATTRIBUTE_CAPTUREDEF(Attack)

	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor)

	DECLARE_ATTRIBUTE_CAPTUREDEF(Health)

	void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const;
};
