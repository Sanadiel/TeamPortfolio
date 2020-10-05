// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_MonsterAttack.h"

void UAnimNotify_MonsterAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	UE_LOG(LogClass, Warning, TEXT("Player Attack"));
}
