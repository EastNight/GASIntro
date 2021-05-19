// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GroundSelectTargetActor.generated.h"

/**
 * 
 */
UCLASS()
class GASINTRO_API AGroundSelectTargetActor : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
	
public:

	virtual void StartTargeting(UGameplayAbility* Ability) override;

	virtual void ConfirmTargetingAndContinue() override;

	UFUNCTION(BlueprintCallable,Category = "GroundSelectTargetActor")
	bool GetPlayerLookingPoint(FVector& out_LookingPoint);

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(ExposeOnSpawn = true),  Category = "GroundSelectTargetActor")
	float SelectRadius;
};
