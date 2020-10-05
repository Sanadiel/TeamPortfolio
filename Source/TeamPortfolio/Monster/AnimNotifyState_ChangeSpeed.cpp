// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_ChangeSpeed.h"
#include "Monster.h"

void UAnimNotifyState_ChangeSpeed::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{


	AMonster* Monster = Cast<AMonster>(MeshComp->GetOwner());
	if (Monster)
	{
		Monster->SetSpeed(3);
	}
}

void UAnimNotifyState_ChangeSpeed::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	AMonster* Monster = Cast<AMonster>(MeshComp->GetOwner());
	if (Monster)
	{
		Monster->SetSpeed(3);
	}

}

void UAnimNotifyState_ChangeSpeed::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AMonster* Monster = Cast<AMonster>(MeshComp->GetOwner());
	if (Monster)
	{
		Monster->SetSpeed(150);
	}
}
