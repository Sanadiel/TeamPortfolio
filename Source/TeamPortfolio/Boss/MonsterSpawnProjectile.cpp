// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawnProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshcomponent.h"
// Sets default values
AMonsterSpawnProjectile::AMonsterSpawnProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Use a sphere as a simple collision representation
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->InitSphereRadius(10.0f);
	Sphere->BodyInstance.SetCollisionProfileName("Projectile");

	// Players can't walk on it
	Sphere->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	Sphere->CanCharacterStepUpOn = ECB_No;

	SetRootComponent(Sphere);

	Sphere->SetSimulatePhysics(true);
	Sphere->SetEnableGravity(true);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Sphere->SetNotifyRigidBodyCollision(true);


	//MeshSetting
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));
	Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, -15.0f));

	SetReplicates(true);
	SetReplicateMovement(true);


	/* Deprecated.
	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = Sphere;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;


	// Die after 3 seconds by default
	//InitialLifeSpan = 3.0f;
	*/

}

// Called when the game starts or when spawned
void AMonsterSpawnProjectile::BeginPlay()
{
	Super::BeginPlay();

	// set up a notification for when this component hits something blocking.

	Sphere->OnComponentHit.AddDynamic(this, &AMonsterSpawnProjectile::OnHit);
}

//// Called every frame
//void AMonsterSpawnProjectile::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

void AMonsterSpawnProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		//Don't Impulse to Projectile.
		if (OtherActor->IsA(AMonsterSpawnProjectile::StaticClass()))
		{
			return;
		}

		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}
	else if (OtherActor != NULL && OtherActor != this && OtherComp != NULL) //Spawn Monster when Hit Ground -> Not SimulatingPhysics.
	{
		if (HasAuthority() && MonsterSpawnInfo.SpawnActorClass) // Only Do in Server
		{
			SpawnMonster(Hit);
		}
		else
		{
			UE_LOG(LogClass, Warning, TEXT("You Don't Assign MonsterActorClass in \"MonsterSpawnProjectileClass\"... Maybe?"))
		}
		Destroy();
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("other actor is null? otheractor is this? othercompo NULL?"))
	}
}

void AMonsterSpawnProjectile::SpawnMonster_Implementation(const FHitResult& Hit)
{
	//Spawn Monster 
	if (MonsterSpawnInfo.SpawnActorClass)
	{
		FTransform transform;
		transform.SetLocation(Hit.Location);
		FActorSpawnParameters params;
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		params.Owner = GetOwner();
		//UE_LOG(LogClass, Warning, TEXT("Owner : %s"), *GetOwner()->GetName());
		AActor* monster = GetWorld()->SpawnActor<AActor>(MonsterSpawnInfo.SpawnActorClass, transform, params);

		if (!monster)		//Check Monster Spawn Success.
		{
			//Don't CoolDown Start
			UE_LOG(LogClass, Warning, TEXT("Failed to Spawn Monster"));
		}
	}

}

