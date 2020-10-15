// Fill out your copyright notice in the Description page of Project Settings.


#include "TeamP_AnimInstance.h"
#include "TeamP_BasicPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"



void UTeamP_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


	ATeamP_BasicPlayer* Pawn = Cast< ATeamP_BasicPlayer>(TryGetPawnOwner());
	if (Pawn && Pawn->IsValidLowLevel()) {
		bIsCrouched = Pawn->bIsCrouched;
	
		Speed = Pawn->GetCharacterMovement()->Velocity.Size();

		Direction = CalculateDirection(Pawn->GetCharacterMovement()->Velocity, Pawn->GetActorRotation());
		
		bIsIronsight = Pawn->bIsIronsight;

		bIsReload = Pawn->bIsReload;

		bIsShotgun = Pawn->bIsShotgun;

		//bFireShotgun = Pawn->bFireShotgun;

		if (!bIsShotgun) {
			bIsFireAnim = Pawn->bIsFireAnim; 
		}

		if (bIsShotgun) {
			if (Pawn->bFireShotgun) {
				bFireShotgun = Pawn->bFireShotgun;
				bIsFireAnim = Pawn->bIsFireAnim;
			}
			else {
				bIsFireAnim = false;
				Pawn->bFireShotgun = false;
			}
		}
		

		FRotator AimRotation = Pawn->GetAimOffset();
		AimYaw = AimRotation.Yaw;
		AimPitch = AimRotation.Pitch;

		if (Pawn->bIsReload && Pawn->ReloadMontage)
		{
			if (!Montage_IsPlaying(Pawn->ReloadMontage))
			{
				Pawn->PlayAnimMontage(Pawn->ReloadMontage);
			}
		}

	}
}

void UTeamP_AnimInstance::Animnotify_ReloadEnd(UAnimNotify* Animnotify)
{
	ATeamP_BasicPlayer* Pawn = Cast<ATeamP_BasicPlayer>(TryGetPawnOwner());
	if (Pawn && Pawn->IsValidLowLevel()) 
	{
		bIsReload = false;
		Pawn->bIsReload = false;
	}
}
