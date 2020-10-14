// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlotBase.h"
#include "Components/Button.h"
#include "ItemWidgetBase.h"
#include "InventoryWidgetBase.h"
#include "ItemTooltipBase.h"
#include "../Item/MasterItem.h"
#include "Components/CanvasPanel.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "TestUI_PC.h"
#include "../Item/Inventory.h"
#include "MainUIBase.h"
#include "EquipmentBase.h"

void UItemSlotBase::NativeConstruct()
{
	Super::NativeConstruct();
		
	ItemWidget = Cast<UItemWidgetBase>(GetWidgetFromName(TEXT("ItemWidget")));	
}

void UItemSlotBase::UpdateItemSlot(AMasterItem* Item)
{
	if (Item)
	{
		ItemWidget->UpdateItemSlot(Item);
	}
}

void UItemSlotBase::SetInvenParent(UInventoryWidgetBase * InvenParent)
{
	InvenWidget = InvenParent;
}

void UItemSlotBase::SetMainUIRootCanvas(UCanvasPanel* Canvas)
{
	MainUIRootCanvas = Canvas;
}

FItemDataTable UItemSlotBase::GetThisItemData()
{	
	return ItemWidget->Item->ItemData;
}

bool UItemSlotBase::GetisDraging()
{
	return InvenWidget->GetisDraging();
}

void UItemSlotBase::TooltipVisible(bool bValue)
{
	if (GetThisItemData().ItemIndex == CN_NullItemIndex)
		return;

	UItemTooltipBase* pTooltip = InvenWidget->GetTooltipWidget();
	
	if (bValue == true)
	{
		pTooltip->SetTooltipsInfo(GetThisItemData().ItemName, GetThisItemData().ItemName, GetThisItemData().ItemThumnail);
		pTooltip->SetVisibility(ESlateVisibility::HitTestInvisible);
		pTooltip->AddToViewport(1);
	}
	else
	{
		pTooltip->SetVisibility(ESlateVisibility::Collapsed);
		pTooltip->RemoveFromParent();
	}	
}

void UItemSlotBase::SetisDraging(bool bValue)
{
	InvenWidget->SetisDraging(bValue);
	TooltipVisible(false);
}

void UItemSlotBase::NativeOnMouseEnter(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (GetisDraging() == false)
	{
		FVector2D NewPosition = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition()) +
			MainUIRootCanvas->GetCachedGeometry().AbsoluteToLocal(InGeometry.GetAbsolutePosition());

		InvenWidget->GetTooltipWidget()->SetPositionInViewport(NewPosition, false);

		TooltipVisible(true);
	}
}

void UItemSlotBase::NativeOnMouseLeave(const FPointerEvent & InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	if (GetisDraging() == false)
	{
		TooltipVisible(false);
	}
}

FReply UItemSlotBase::NativeOnMouseMove(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
	Super::NativeOnMouseMove(InGeometry, InMouseEvent);

	FEventReply Reply = UWidgetBlueprintLibrary::Handled();

	FVector2D NewPosition = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition()) +
		MainUIRootCanvas->GetCachedGeometry().AbsoluteToLocal(InGeometry.GetAbsolutePosition());

	InvenWidget->GetTooltipWidget()->SetPositionInViewport(NewPosition, false);

	return Reply.NativeReply;
}

FReply UItemSlotBase::NativeOnMouseButtonDown(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	FEventReply Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);//FReply::Handled().DetectDrag(this?, EKeys::LeftMouseButton);

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		ATestUI_PC* PC = GetOwningPlayer<ATestUI_PC>();

		if (SlotType == ESlotParentType::Inventory)//�κ��丮���� ����
		{
			//�Һ��� -> ���
			if (ItemWidget->GetItem()->ItemData.ItemType == EItemType::Consume)
			{
				ItemWidget->UseConsumeItem();
				ItemWidget->UpdateCount();
			}
			//������ -> ������ ��ġ�� ����
			else if (ItemWidget->GetItem()->ItemData.ItemType == EItemType::Equip)
			{				
				ESlotType SlotNum = ItemWidget->GetItem()->ItemData.ItemEquipSlot;

				AMasterItem* MasterItem = PC->Inventory->Equipment[(int)SlotNum];
				PC->Inventory->Equipment[(int)SlotNum] = PC->Inventory->Inven[SlotIndex];
				PC->Inventory->Equipment[(int)SlotNum]->ItemIndex = PC->Inventory->Equipment[(int)SlotNum]->ItemData.ItemIndex;
				PC->Inventory->Inven[SlotIndex] = MasterItem;
				UpdateItemSlot(PC->Inventory->Inven[SlotIndex]);
				PC->MainWidgetObject->EquipWindow->SetSlot((int)SlotNum, PC->Inventory->Equipment[(int)SlotNum]);				
			}
		}
		else if(SlotType == ESlotParentType::Equipment)//���â���� ����
		{//��������
			int EmptySlotNum = PC->MainWidgetObject->Inventory->GetEmptySlot();

			AMasterItem* MasterItem = PC->Inventory->Equipment[SlotIndex];
			PC->Inventory->Equipment[SlotIndex] = PC->Inventory->Inven[EmptySlotNum];
			PC->Inventory->Equipment[SlotIndex]->ItemIndex = PC->Inventory->Equipment[SlotIndex]->ItemData.ItemIndex;
			PC->Inventory->Inven[EmptySlotNum] = MasterItem;
			UpdateItemSlot(PC->Inventory->Equipment[SlotIndex]);
			PC->MainWidgetObject->Inventory->SetSlot(EmptySlotNum, PC->Inventory->Inven[EmptySlotNum]);
		}
		else if (SlotType == ESlotParentType::Shop)
		{
			//����
			//���� �Ϲ��� -> �׳� ��ĭ ����
			//�Һ��� -> �������ߵ�
			//��� ��ƾߵ�
			
			//AMasterItem* MasterItem = ;
			//int ExistIndex = PC->MainWidgetObject->Inventory->HaveThis(MasterItem);
			//if (MasterItem->ItemData.ItemType == EItemType::Consume && ExistIndex != -1)//��ġ��
			//{
			//	PC->Inventory->Inven[ExistIndex]->ItemData.ItemCount += 1;
			//	PC->MainWidgetObject->Inventory->UpdateInventoryWithIndex(PC->Inventory->Inven, ExistIndex);
			//}
			//else//�׳� ����
			//{
			//	int EmptySlotNum = PC->MainWidgetObject->Inventory->GetEmptySlot();

			//	PC->Inventory->Inven[EmptySlotNum] = MasterItem;
			//	PC->Inventory->Equipment[SlotIndex] = PC->Inventory->Inven[EmptySlotNum];
			//	PC->Inventory->Equipment[SlotIndex]->ItemIndex = PC->Inventory->Equipment[SlotIndex]->ItemData.ItemIndex;
			//	PC->Inventory->Inven[EmptySlotNum] = MasterItem;
			//	PC->MainWidgetObject->Inventory->SetSlot(EmptySlotNum, PC->Inventory->Inven[EmptySlotNum]);
			//}
		}
	}	

	return Reply.NativeReply;
}

