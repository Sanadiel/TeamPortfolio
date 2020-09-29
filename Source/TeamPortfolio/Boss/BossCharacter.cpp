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
#include "PhysicsEngine/PhysicsHandleComponent.h" // Physics Handle.
#include "Components/SphereComponent.h"
// Sets default values
ABossCharacter::ABossCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*Setting Appearance*/
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->SocketOffset = FVector(0.0f, 40.0f, 88.0f);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));

	//PhysicsHandle Component.
	PhysicsHandle  = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
	
	//HoldPosition.
	HoldPosition = CreateDefaultSubobject<USceneComponent>(TEXT("HoldPosition"));
	HoldPosition->SetupAttachment(Camera);
	HoldPosition->SetRelativeLocation(FVector(200.0f,0.0f,-50.0f));

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = false;

	//Boss Will Exist in Level. Normal Player will Spawn by GameMode.
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	/* Deprecated. 
	//Trajectory Param's Default Parameter. Not Needed when Throwing PlayMode
	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
	objectTypes.Add(EObjectTypeQuery::ObjectTypeQuery1);
	TrajectoryParams.ObjectTypes = objectTypes;
	TrajectoryParams.DrawDebugType = EDrawDebugTrace::ForOneFrame;
	TrajectoryParams.SimFrequency = 15.0f;
	TrajectoryParams.MaxSimTime = 2.0f;
	TrajectoryParams.ProjectileRadius = 10.0f;
	*/
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

	/*Show Mouse Cursor*/
	APlayerController* pc = Cast<APlayerController>(GetController());
	if (pc)
	{
		pc->bShowMouseCursor = true;
		pc->SetInputMode(FInputModeGameAndUI());
	}
	
	//Initialize Spawn Cooldown.
	for (int i = 0; i < SpawnClasses.Num(); i++)
	{
		SpawnCooldown.Add(0.0f);
		MaxSpawnCooldown.Add(SpawnClasses[i].GetDefaultObject()->MonsterSpawnInfo.Cooldown);
	}

}

// Called every frame
void ABossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//DrawProjectileTrajectory();

	for (int i = 0; i < SpawnCooldown.Num(); i++)
	{
		SpawnCooldown[i] += DeltaTime;
		SpawnCooldown[i] = FMath::Clamp<float>(SpawnCooldown[i], 0.0f, MaxSpawnCooldown[i]);
	}

	//PhysicsHandle Needed Update Target Location Per Frame.
	if (PhysicsHandle)
	{
		PhysicsHandle->SetTargetLocation(HoldPosition->GetComponentLocation());
	}
}

// Called to bind functionality to input
void ABossCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABossCharacter::ReleaseSpawnProjectile);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABossCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABossCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ABossCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ABossCharacter::LookUp);

}

//void ABossCharacter::DrawProjectileTrajectory()
//{
//
//	//Adjust Location to ActorLocation & LaunchVelocity... will equal to Projectile Speed I Think?
//	TrajectoryParams.StartLocation = GetActorLocation();
//	TrajectoryParams.LaunchVelocity = UKismetMathLibrary::GetForwardVector(GetControlRotation()) * 3000.0f;
//	UGameplayStatics::PredictProjectilePath(GetWorld(), TrajectoryParams, Trajectoryresult);
//
//}

//void ABossCharacter::FireToSpawn()
//{
//	//Fire Monster Spawn Projectile if Valid.
//	if (MonsterSpawnProjectileClass)
//	{
//		FTransform transform;
//		transform.SetLocation(GetActorLocation() + GetActorForwardVector() * 100.0f);
//		transform.SetRotation(GetControlRotation().Quaternion());
//		GetWorld()->SpawnActor<AMonsterSpawnProjectile>(MonsterSpawnProjectileClass, transform);
//	}
//}

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
	FRotator controlRot = FRotator(0.0f, cameraRotation.Yaw, 0.0f);
	FVector temp = UKismetMathLibrary::GetForwardVector(controlRot);

	AddMovementInput(temp, Value);
}

void ABossCharacter::MoveRight(float Value)
{

	FVector cameraLocation;
	FRotator cameraRotation;

	GetController()->GetPlayerViewPoint(cameraLocation, cameraRotation);
	FRotator controlRot = FRotator(0.0f, cameraRotation.Yaw, 0.0f);
	FVector temp = UKismetMathLibrary::GetRightVector(controlRot);

	AddMovementInput(temp, Value);
}

void ABossCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ABossCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void ABossCharacter::HoldSpawnProjectile_Implementation(AMonsterSpawnProjectile* ProjectileObject)
{
	if (PhysicsHandle && ProjectileObject)
	{
		PhysicsHandle->GrabComponentAtLocation(ProjectileObject->Sphere, NAME_None, ProjectileObject->GetActorLocation());
		//UE_LOG(LogClass, Warning, TEXT("Hold OK"));
	}
}

void ABossCharacter::ReleaseSpawnProjectile()
{
	PhysicsHandle->ReleaseComponent();
}

UPrimitiveComponent * ABossCharacter::GetGrabbedComponent() const
{
	return PhysicsHandle->GetGrabbedComponent();
}
