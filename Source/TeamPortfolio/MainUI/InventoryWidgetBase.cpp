// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidgetBase.h"
#include "Components/WrapBox.h"
#include "Components/InvalidationBox.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "MainUIBase.h"
#include "ItemSlotBase.h"
#include "ItemWidgetBase.h"
#include "ItemTooltipBase.h"
#include "TestUI_PC.h"
#include "../Item/Inventory.h"
#include "../Item/MasterItem.h"

void UInventoryWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	ItemSlots = Cast<UWrapBox>(GetWidgetFromName(TEXT("WrapBox_Item")));
	Drag = Cast<UBorder>(GetWidgetFromName(TEXT("Drag")));
	Exit = Cast<UButton>(GetWidgetFromName(TEXT("Exit")));

	if (Exit)
	{
		Exit->OnClicked.AddDynamic(this, &UInventoryWidgetBase::OnExitButton);
	}
}

void UInventoryWidgetBase::UpdateInventory(TArray<class AMasterItem*> Inventory)
{
	for (int i = 0; i < Inventory.Num(); ++i)
	{
		SetSlot(i, Inventory[i]);
		/*int FindIndex = GetEmptySlot();
		if (FindIndex > -1)
		{
			SetSlot(FindIndex, Inventory[i]);
		}*/
	}
}

void UInventoryWidgetBase::UpdateInventoryWithIndex(TArray<class AMasterItem*> Inventory, int32 FirstIndex)
{
	SetSlot(FirstIndex, Inventory[FirstIndex]);
}

int UInventoryWidgetBase::GetEmptySlot()
{
	for (int Index = 0; Index < ItemSlots->GetChildrenCount(); ++Index)
	{
		UItemSlotBase* InventorySlot = Cast<UItemSlotBase>(ItemSlots->GetChildAt(Index));		

		if (InventorySlot)
		{
			if (IsValid(InventorySlot->ItemWidget->Item))
			{
				if (InventorySlot->ItemWidget->Item->ItemIndex == CN_NullItemIndex)
				{
					return Index;
				}//아이템이 존재하는데 널이 아니면 있으니 다음으로 진행
			}
			else//아이템이 없으니 생성
			{
				return Index;
			}
		}
	}

	return -1;
}

void UInventoryWidgetBase::SetSlot(int Index, AMasterItem* Item)
{
	UItemSlotBase* EmptySlot = Cast<UItemSlotBase>(ItemSlots->GetChildAt(Index));
	
	if (EmptySlot && Item->ItemIndex == CN_NullItemIndex)
	{
		EmptySlot->UpdateItemSlot(Item);
		EmptySlot->ItemWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		EmptySlot->UpdateItemSlot(Item);
		EmptySlot->ItemWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

void UInventoryWidgetBase::SetSlotsParent()
{
	for (int index = 0; index < ItemSlots->GetChildrenCount(); ++index)
	{
		UItemSlotBase* ChildSlot = Cast<UItemSlotBase>(ItemSlots->GetChildAt(index));
		ChildSlot->SetInvenParent(this);
		ChildSlot->SetMainUIRootCanvas(MainUIParent->RootCanvas);
	}
}

void UInventoryWidgetBase::SetMainUIParent(UMainUIBase* MainUI)
{
	MainUIParent = MainUI;
}

bool UInventoryWidgetBase::GetisDraging()
{	
	return MainUIParent->isDraging;
}

void UInventoryWidgetBase::SetisDraging(bool bValue)
{
	MainUIParent->isDraging = bValue;
}

FItemDataTable UInventoryWidgetBase::GetItemData(int32 Index)
{
	ATestUI_PC* PC = GetOwningPlayer<ATestUI_PC>();
	return PC->Inventory->GetItemData(Index);
}

UItemTooltipBase* UInventoryWidgetBase::GetTooltipWidget()
{
	return MainUIParent->ItemHover;
}

void UInventoryWidgetBase::SwapSlot(int32 FrontslotIndex, int32 OtherSlotIndex)
{
	ATestUI_PC* PC = GetOwningPlayer<ATestUI_PC>();
	PC->Inventory->SwapSlot(FrontslotIndex, OtherSlotIndex);
	UpdateInventoryWithIndex(PC->Inventory->Inven, FrontslotIndex);
	UpdateInventoryWithIndex(PC->Inventory->Inven, OtherSlotIndex);
}

void UInventoryWidgetBase::OnExitButton()
{
	ATestUI_PC* PC = GetOwningPlayer<ATestUI_PC>();
	PC->UnToggle_InvenWidget();
}