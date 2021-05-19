// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "DetectAroundTargetActor.generated.h"

/**
 * 
 */
UCLASS()
class GASINTRO_API ADetectAroundTargetActor : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
	
public:

	virtual void StartTargeting(UGameplayAbility* Ability) override;

	virtual void ConfirmTargetingAndContinue() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "DetectAroundTargetActor")
	float DetectRadius;
};
