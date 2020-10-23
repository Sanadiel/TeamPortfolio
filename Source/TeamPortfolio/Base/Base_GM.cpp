// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_GM.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

AActor* ABase_GM::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	if (IncomingName == TEXT(""))
	{
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), OutActors);
		return OutActors[0];
	}
	else
	{
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), OutActors);

		for (int Index = 0; Index != OutActors.Num(); ++Index)
		{
			APlayerStart* PS = Cast< APlayerStart>(OutActors[Index]);

			if (IncomingName == PS->PlayerStartTag.ToString())
			{
				return PS;
			}
		}

		//없는 경우
		return OutActors[0];
	}
}

void ABase_GM::Replace_AllPlayers_Implementation()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerController::StaticClass(), OutActors);

	for (int Index = 0; Index != OutActors.Num(); ++Index)
	{
		APlayerController* PC = Cast<APlayerController>(OutActors[Index]);

		if (PC->ActorHasTag(TEXT("Defence")))
		{
			AActor* Defence = FindPlayerStart_Implementation(PC, TEXT("Defence"));
			PC->GetPawn()->SetActorTransform(Defence->GetTransform());
		}
		else
		{
			AActor* Offence = FindPlayerStart_Implementation(PC, TEXT("Offence"));
			PC->GetPawn()->SetActorTransform(Offence->GetTransform());
		}
	}
}

void ABase_GM::Replace_Player_Implementation(AController* Player)
{
	AActor* PS = FindPlayerStart_Implementation(Player, Player->Tags[0].ToString());
	Player->GetPawn()->SetActorTransform(PS->GetTransform());
}
