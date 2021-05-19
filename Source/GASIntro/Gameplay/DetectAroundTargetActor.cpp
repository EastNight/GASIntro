// Fill out your copyright notice in the Description page of Project Settings.


#include "GASIntro/Gameplay/DetectAroundTargetActor.h"
#include "Abilities//GameplayAbility.h"
#include "GameFramework/PlayerController.h"

void ADetectAroundTargetActor::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);
	MasterPC = Cast<APlayerController>(Ability->GetOwningActorFromActorInfo()->GetInstigatorController());
}

void ADetectAroundTargetActor::ConfirmTargetingAndContinue()
{
	APawn* MasterPawn = MasterPC->GetPawn();
	if (!MasterPawn)
	{
		return;
	}

	FVector PawnLocation = MasterPawn->GetActorLocation();

	TArray<FOverlapResult> OverlapResults;
	TArray<TWeakObjectPtr<AActor>> OverlapedActors;

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = false;
	QueryParams.bReturnPhysicalMaterial = false;
	if (MasterPawn)
	{
		QueryParams.AddIgnoredActor(MasterPawn);
	}
	bool QueryResult = GetWorld()->OverlapMultiByObjectType(
		OverlapResults,
		PawnLocation,
		FQuat::Identity,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_Pawn),
		FCollisionShape::MakeSphere(DetectRadius),
		QueryParams
	);

	if (QueryResult)
	{
		for (int i = 0; i < OverlapResults.Num(); i++)
		{
			APawn* OverlappedPawn = Cast<APawn>(OverlapResults[i].GetActor());
			if (OverlappedPawn && !OverlapedActors.Contains(OverlappedPawn))
			{
				OverlapedActors.Add(OverlappedPawn);
			}
		}
	}

	FGameplayAbilityTargetDataHandle TargetDataHandle;

	if (OverlapedActors.Num() > 0)
	{
		FGameplayAbilityTargetData_ActorArray* ActorArray = new FGameplayAbilityTargetData_ActorArray();
		ActorArray->SetActors(OverlapedActors);
		TargetDataHandle.Add(ActorArray);
	}

	check(ShouldProduceTargetData());
	if (IsConfirmTargetingAllowed())
	{
		TargetDataReadyDelegate.Broadcast(TargetDataHandle);
	}
}
