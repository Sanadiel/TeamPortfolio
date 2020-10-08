// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_MonsterAttack.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Components/SkeletalMeshComponent.h"


void UAnimNotify_MonsterAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	AActor* Monster = MeshComp->GetOwner();

	UKismetSystemLibrary::PrintString(Monster->GetWorld(), TEXT("MonsterAttack"));

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjecTypes;
	ObjecTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(Monster);
	
	TArray<AActor*>OutActors;

	bool bResult = UKismetSystemLibrary::SphereOverlapActors(
		Monster->GetWorld(),
		Monster->GetActorLocation(),
		200.0f,
		ObjecTypes,
		AActor::StaticClass(),
		IgnoreActors,
		OutActors

	);

	if (bResult)
	{
		UGameplayStatics::ApplyDamage(OutActors[0],
			30.0f,
			nullptr,
			Monster,
			nullptr
		);
	}

}
