// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BaseGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class ECostType : uint8
{
	Health,
	Mana,
	Strength
};

USTRUCT(BlueprintType)
struct FGameplayAbilityInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "BaseGameplayAbility")
	float CoolDown;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "BaseGameplayAbility")
	float Cost;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "BaseGameplayAbility")
	ECostType CostType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseGameplayAbility")
	UMaterialInstance* IconMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseGameplayAbility")
	TSubclassOf<UBaseGameplayAbility> AbilityClass;

	FGameplayAbilityInfo();

	FGameplayAbilityInfo(float CoolDown, float Cost, ECostType CostType, UMaterialInstance* IconMaterial, TSubclassOf<UBaseGameplayAbility> AbilityClass);
};


/**
 * 
 */
UCLASS()
class GASINTRO_API UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseGameplayAbility")
	UMaterialInstance* IconMaterial;

	UFUNCTION(BlueprintCallable, Category = "BaseGameplayAbility")
	FGameplayAbilityInfo GetAbilityInfo();
};
