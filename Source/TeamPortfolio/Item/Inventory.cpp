// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "MasterItem.h"


UInventory::UInventory()
{
	PrimaryComponentTick.bCanEverTick = false;
	Inven.Reserve(CN_InventoryMaxChild);
}

void UInventory::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i != CN_InventoryMaxChild; ++i)
	{
		AMasterItem* MasterItem = NewObject<AMasterItem>();
		MasterItem->SettingByIndex(FMath::RandRange(0, 6), GetWorld());
		Inven.Add(MasterItem);
		MasterItem->ConditionalBeginDestroy();
	}

	for (int i = 0; i != CN_EquipMaxChild; ++i)
	{
		AMasterItem* MasterItem = NewObject<AMasterItem>();
		MasterItem->SettingByIndex(CN_NullItemIndex, GetWorld());
		Equipment.Add(MasterItem);
		MasterItem->ConditionalBeginDestroy();
	}
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

bool UInventory::isNull(int32 Index)
{
	if (Inven[Index]->ItemIndex == CN_NullItemIndex)
	{
		return true;
	}
	else
	{
		return false;
	}
}

