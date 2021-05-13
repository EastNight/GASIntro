// Fill out your copyright notice in the Description page of Project Settings.

#include "GASIntro/Characters/BaseCharacter.h"
#include "GASIntro/Gameplay/BaseAttributeSet.h"
#include "AbilitySystemComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UBaseAttributeSet>("AttributeSet");
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABaseCharacter::AquireAbility(TSubclassOf<UBaseGameplayAbility> Ability)
{
	if (AbilitySystemComponent && Ability)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability));
		// NetMode Owner PlayState, Avator this
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

