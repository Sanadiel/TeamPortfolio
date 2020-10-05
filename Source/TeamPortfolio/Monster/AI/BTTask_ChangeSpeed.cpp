// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChangeSpeed.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "../MonsterAIController.h"

EBTNodeResult::Type UBTTask_ChangeSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMonsterAIController* AIC = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (AIC)
	{
		ACharacter* Pawn = Cast<ACharacter>(AIC->GetPawn());
		if (Pawn)
		{
			float NewSpeed = AIC->BBComponent->GetValueAsFloat(GetSelectedBlackboardKey());
			Pawn->GetCharacterMovement()->MaxWalkSpeed = NewSpeed;

			return EBTNodeResult::Succeeded;

		}
	}
	return EBTNodeResult::Type();
}
