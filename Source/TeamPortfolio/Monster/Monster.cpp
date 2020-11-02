// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "MonsterAIController.h"
#include "../Instance/TotalLog_GameInstance.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMonster::AMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocation(FVector(0, 0, -GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()));
	GetMesh()->SetRelativeRotation(FRotator(0, -90.0f, 0));

	Tags.Add(TEXT("Monster"));

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));


	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();

	SetSpeed(WalkSpeed);

	if (PawnSensing)
	{
		PawnSensing->OnSeePawn.AddDynamic(this, &AMonster::ProcessSeenPawn);
		PawnSensing->OnHearNoise.AddDynamic(this, &AMonster::ProcessHeardPawn);
	}
	
	
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMonster::ProcessSeenPawn(APawn* Pawn)
{
	if (Pawn->ActorHasTag(TEXT("Player")) &&
		CurrentState == EMonsterState::Normal)
	{
		UE_LOG(LogClass, Warning, TEXT("See %s"), *Pawn->GetName());
		SetCurrentState(EMonsterState::Chase);
		
		AMonsterAIController* AIC = GetController<AMonsterAIController>();
		if (AIC)
		{
			AIC->SetPlayer(Pawn);
		}

	}
}

void AMonster::ProcessHeardPawn(APawn* Pawn, const FVector& Location, float Volume)
{
	UE_LOG(LogClass, Warning, TEXT("Heard %s"), *Pawn->GetName());
}

void AMonster::SetCurrentState(EMonsterState NewState)
{
	

	AMonsterAIController* AIC = GetController<AMonsterAIController>();
	if (AIC)
	{
		CurrentState = NewState;
		AIC->SetCurrnetState(NewState);
	}
}

void AMonster::SetSpeed(float NewSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
}

void AMonster::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMonster, CurrentHP);
}

float AMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	CurrentHP -= DamageAmount;
	CurrentHP = FMath::Clamp(CurrentHP, 0.0f, 100.0f);

	if (CurrentHP <= 0)
	{
		SetCurrentState(EMonsterState::Death);
	}

	return 0.0f;
}

void AMonster::Destroyed()
{
	UTotalLog_GameInstance* GI = Cast< UTotalLog_GameInstance>(GetGameInstance());

	if (IsValid(GI))
	{
		GI->Monster_Record[MonType] += 1;

		UE_LOG(LogClass, Warning, TEXT("%d"), GI->Monster_Record[MonType]);
	}		

	Super::Destroyed();
}


void AMonster::C2S_DamageProcess_Implementation()
{
	
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("MonsterAttack"));

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjecTypes;
	ObjecTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel3));

	TArray<AActor*> IgnoreActors;
	//IgnoreActors.Add(Monster);

	TArray<AActor*>OutActors;

	bool bResult = UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(),
		GetActorLocation(),
		200.0f,
		ObjecTypes,
		AActor::StaticClass(),
		IgnoreActors,
		OutActors

	);
	//UE_LOG(LogClass, Warning, TEXT("%s"), OutActors[0]);

	if (bResult)
	{
		UGameplayStatics::ApplyDamage(OutActors[0],
			30.0f,
			nullptr,
			this,
			nullptr
		);
	}
	
}