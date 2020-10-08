// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidgetBase.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "../Item/MasterItem.h"
#include "Engine/StreamableManager.h"

void UItemWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	ItemThumnail = Cast<UBorder>(GetWidgetFromName(TEXT("ItemThumnail")));	
	ItemCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemCount")));
}

void UItemWidgetBase::UpdateItemSlot(AMasterItem* ParamItem)
{
	if (ParamItem)
	{		
		FStreamableManager Loader;

		Item = ParamItem;
		ItemThumnail->SetBrushFromTexture(Loader.LoadSynchronous<UTexture2D>(Item->ItemData.ItemThumnail));
		ItemCount->SetText(FText::FromString(FString::FromInt(Item->ItemData.ItemCount)));
	}
}