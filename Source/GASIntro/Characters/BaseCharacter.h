// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GASIntro/Gameplay/BaseGameplayAbility.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class GASINTRO_API ABaseCharacter : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BaseCharacter")
	class UAbilitySystemComponent* AbilitySystemComponent;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BaseCharacter")
	class UBaseAttributeSet* AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseCharacter")
	FGameplayTag FullHealthTag;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Returns the ability system component to use for this actor. It may live on another actor, such as a Pawn using the PlayerState's component */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

	UFUNCTION(BlueprintCallable,Category = "BaseCharacter")
	FGameplayAbilityInfo AquireAbility(TSubclassOf<UBaseGameplayAbility> Ability);

	void AddGameplayTag(FGameplayTag& Tag,int Count);

	void RemoveGameplayTag(FGameplayTag& Tag,int Count);
};
