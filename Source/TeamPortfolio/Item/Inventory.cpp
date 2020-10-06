// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "MasterItem.h"


UInventory::UInventory()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventory::BeginPlay()
{
	Super::BeginPlay();
}

void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInventory::SwapSlot(int32 Slot, int32 OtherSlot)
{
	Inven.Swap(Slot, OtherSlot);
}

FItemDataTable UInventory::GetItemData(int32 InvenIndex)
{
	return Inven[InvenIndex]->ItemData;
}

void UInventory::DataLoading()
{
}

