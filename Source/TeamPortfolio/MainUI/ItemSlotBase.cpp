// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlotBase.h"
#include "Components/Button.h"
#include "ItemWidgetBase.h"
#include "InventoryWidgetBase.h"
#include "ItemTooltipBase.h"
#include "../Item/MasterItem.h"
#include "Components/CanvasPanel.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

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

void UItemSlotBase::SetEquipParent(UInventoryWidgetBase* InvenParent)
{
	
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

		UE_LOG(LogClass, Warning, TEXT("%f, %f"), NewPosition.X, NewPosition.Y);

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
		UE_LOG(LogClass, Warning, TEXT("RightButton"));

		if (SlotType == ESlotParentType::Inventory)
		{
			//소비재 -> 사용
			//장착템 -> 장착템 위치와 스왑
		}
		else if(SlotType == ESlotParentType::Equipment)
		{
			//장착해제
		}
		else if (SlotType == ESlotParentType::Shop)
		{
			//구입
		}
	}

	

	return Reply.NativeReply;
}

