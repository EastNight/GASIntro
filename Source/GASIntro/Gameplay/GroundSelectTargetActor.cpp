// Fill out your copyright notice in the Description page of Project Settings.


#include "GASIntro/Gameplay/GroundSelectTargetActor.h"
#include "Abilities//GameplayAbility.h"
#include "GameFramework/PlayerController.h"

void AGroundSelectTargetActor::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);
	MasterPC = Cast<APlayerController>(Ability->GetOwningActorFromActorInfo()->GetInstigatorController());
}

void AGroundSelectTargetActor::ConfirmTargetingAndContinue()
{
	FVector LookingPoint;
	GetPlayerLookingPoint(LookingPoint);

	TArray<FOverlapResult> OverlapResults;
	TArray<TWeakObjectPtr<AActor>> OverlapedActors;

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = false;
	QueryParams.bReturnPhysicalMaterial = false;
	APawn* MasterPawn = MasterPC->GetPawn();
	if (MasterPawn)
	{
		QueryParams.AddIgnoredActor(MasterPawn);
	}
	bool QueryResult = GetWorld()->OverlapMultiByObjectType(
		OverlapResults,
		LookingPoint,
		FQuat::Identity,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_Pawn),
		FCollisionShape::MakeSphere(SelectRadius),
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

	FGameplayAbilityTargetData_LocationInfo* CenterLocation = new FGameplayAbilityTargetData_LocationInfo();
	CenterLocation->TargetLocation.LiteralTransform = FTransform(LookingPoint);
	CenterLocation->TargetLocation.LocationType = EGameplayAbilityTargetingLocationType::LiteralTransform;
	TargetDataHandle.Add(CenterLocation);

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

bool AGroundSelectTargetActor::GetPlayerLookingPoint(FVector& out_LookingPoint)
{
	FVector ViewLocation;
	FRotator ViewRotation;
	MasterPC->GetPlayerViewPoint(ViewLocation,ViewRotation);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = true;
	APawn* MasterPawn = MasterPC->GetPawn();
	if (MasterPawn)
	{
		QueryParams.AddIgnoredActor(MasterPawn);
	}
	bool TraceResult = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		ViewLocation,
		ViewLocation + ViewRotation.Vector() * 5000.0f,
		ECollisionChannel::ECC_Visibility,
		QueryParams
	);

	if (TraceResult)
	{
		out_LookingPoint = HitResult.ImpactPoint;
	}
	return TraceResult;
}
