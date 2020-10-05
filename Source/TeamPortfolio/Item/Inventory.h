// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEAMPORTFOLIO_API UInventory : public UActorComponent
{
	GENERATED_BODY()
#pragma region Public Member
public:	
	UPROPERTY(BlueprintReadOnly, Visibleanywhere)
	TArray<class AMasterItem*> Inven;

	UPROPERTY(BlueprintReadOnly, Visibleanywhere)
	TArray<class AMasterItem*> Equipment;

#pragma endregion

#pragma region Public Function
	// Sets default values for this component's properties
	UInventory();
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void ChangeSlot(class AMasterItem* A, class AMasterItem* B);

#pragma endregion

#pragma region protected Function
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

#pragma endregion
		
};