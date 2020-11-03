// Fill out your copyright notice in the Description page of Project Settings.


#include "ContactCaseBase.h"
#include "../Item/MasterItem.h"
#include "ContactWidgetBase.h"

void UContactCaseBase::NativeConstruct()
{
	Super::NativeConstruct();
}

void UContactCaseBase::MakeChilren(TArray<AMasterItem*> PickList)
{
	for (int Index = 0; Index != Contact.Num(); ++Index)
	{
		if (Contact[Index]->GetVisibility() == ESlateVisibility::Collapsed)
		{
			PlayAnimationAppear_BlueprintImplement(Contact[Index]);
		}

		Contact[Index]->SetText(PickList[Index]->ItemData.ItemName);
		
	}
}
