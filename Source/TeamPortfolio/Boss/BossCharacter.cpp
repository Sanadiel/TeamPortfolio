// Fill out your copyright notice in the Description page of Project Settings.


#include "BossCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "MonsterSpawnProjectile.h"

#include "BossWidgetBase.h" //Beginplay

// Sets default values
ABossCharacter::ABossCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*Setting Appearance*/
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->SocketOffset = FVector(0.0f, 40.0f*2.0f, 88.0f*2.0f);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));


	/*Trajectory Param's Default Parameter*/
	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
	objectTypes.Add(EObjectTypeQuery::ObjectTypeQuery1);
	TrajectoryParams.ObjectTypes = objectTypes;
	TrajectoryParams.DrawDebugType = EDrawDebugTrace::ForOneFrame;
	TrajectoryParams.SimFrequency = 15.0f;
	TrajectoryParams.MaxSimTime = 2.0f;
	TrajectoryParams.ProjectileRadius = 10.0f;
}

// Called when the game starts or when spawned
void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();

	/*Boss UMG*/
	if (BossWidgetClass)
	{
		UBossWidgetBase* bossWidget = CreateWidget<UBossWidgetBase>(Cast<APlayerController>(GetController()), BossWidgetClass);
		if (bossWidget)
		{
			bossWidget->AddToViewport();
		}
	}

	APlayerController* pc = Cast<APlayerController>(GetController());
	if (pc)
	{
		pc->bShowMouseCursor = true;
		pc->SetInputMode(FInputModeGameAndUI());
	}
	
	for (int i = 0; i < SpawnClasses.Num(); i++)
	{
		SpawnCooldown.Add(0.0f);
	}

}

// Called every frame
void ABossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawProjectileTrajectory();

	for (int i = 0; i < SpawnCooldown.Num(); i++)
	{
		SpawnCooldown[i] += DeltaTime;
	}

}

// Called to bind functionality to input
void ABossCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABossCharacter::FireToSpawn);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABossCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABossCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ABossCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ABossCharacter::LookUp);

}

void ABossCharacter::DrawProjectileTrajectory()
{

	//Adjust Location to ActorLocation & LaunchVelocity... will equal to Projectile Speed I Think?
	TrajectoryParams.StartLocation = GetActorLocation();
	TrajectoryParams.LaunchVelocity = UKismetMathLibrary::GetForwardVector(GetControlRotation()) * 3000.0f;
	UGameplayStatics::PredictProjectilePath(GetWorld(), TrajectoryParams, Trajectoryresult);

}

void ABossCharacter::FireToSpawn()
{
	//Fire Monster Spawn Projectile if Valid.
	if (MonsterSpawnProjectileClass)
	{
		FTransform transform;
		transform.SetLocation(GetActorLocation() + GetActorForwardVector() * 100.0f);
		transform.SetRotation(GetControlRotation().Quaternion());
		GetWorld()->SpawnActor<AMonsterSpawnProjectile>(MonsterSpawnProjectileClass, transform);
	}
}

void ABossCharacter::SetProjectileClass(TSubclassOf<AMonsterSpawnProjectile> NewProjectileClass)
{
	if (NewProjectileClass)
	{
		MonsterSpawnProjectileClass = NewProjectileClass;
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("You Don't Assign NewProjectileClass"))
	}
}

void ABossCharacter::MoveForward(float Value)
{

	FVector cameraLocation;
	FRotator cameraRotation;

	GetController()->GetPlayerViewPoint(cameraLocation, cameraRotation);


	//FRotator controlRot = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);
	FRotator controlRot = FRotator(0.0f, cameraRotation.Yaw, 0.0f);

	FVector temp
		= UKismetMathLibrary::GetForwardVector(controlRot);

	AddMovementInput(temp, Value);
}

void ABossCharacter::MoveRight(float Value)
{

	FVector cameraLocation;
	FRotator cameraRotation;

	GetController()->GetPlayerViewPoint(cameraLocation, cameraRotation);

	//FRotator controlRot = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);
	FRotator controlRot = FRotator(0.0f, cameraRotation.Yaw, 0.0f);

	FVector temp
		= UKismetMathLibrary::GetRightVector(controlRot);

	AddMovementInput(temp, Value);
}

void ABossCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ABossCharacter::LookUp(float Value)
{
	AddControllerPitchInput(-Value);
}
