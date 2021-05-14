// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "BaseAttributeSet.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttributeChangeDelegate, float, CurrentValue, float, MaxValue);

UCLASS()
class GASINTRO_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UBaseAttributeSet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseAttributeSet")
	FGameplayAttributeData Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseAttributeSet")
	FGameplayAttributeData Armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "BaseAttributeSet")
	FGameplayAttributeData Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "BaseAttributeSet")
	FGameplayAttributeData MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseAttributeSet")
	FGameplayAttributeData Mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseAttributeSet")
	FGameplayAttributeData MaxMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseAttributeSet")
	FGameplayAttributeData Strength; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseAttributeSet")
	FGameplayAttributeData MaxStrength;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeDelegate OnHealthChange;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeDelegate OnManaChange;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeDelegate OnStrengthChange;
	
public:
	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
};
