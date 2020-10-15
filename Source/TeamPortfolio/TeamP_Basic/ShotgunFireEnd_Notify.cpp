// Fill out your copyright notice in the Description page of Project Settings.


#include "ShotgunFireEnd_Notify.h"
#include "TeamP_AnimInstance.h"

void UShotgunFireEnd_Notify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	UTeamP_AnimInstance* IM = Cast<UTeamP_AnimInstance>(MeshComp->GetAnimInstance());

	if (IM)
	{
		if (IM->bIsShotgun)
		{
			IM->bFireShotgun = false;
		}
	}
}
