// Fill out your copyright notice in the Description page of Project Settings.


#include "ResultFadeOutBase.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"

void UResultFadeOutBase::NativeConstruct()
{
	Super::NativeConstruct();

	for (int i = 0; i != TextBoxArray_Max; ++i)
	{	
		const FString BoxName = FString::Printf(TEXT("TB_%d"), i);
		UTextBlock* NewBox = Cast<UTextBlock>(GetWidgetFromName(*BoxName));
		TextBoxArray.Add(NewBox);		
	}

	SettingText();
}

void UResultFadeOutBase::SettingText()
{
	for (int i = 0; i != TextBoxArray_Max; ++i)
	{
		FString strText = TextBoxArray[i]->GetText().ToString();
		//FString strText = Instance->GetLog(i).ToString();
		strText += FString::Printf(TEXT(" : %d"), i);		
		TextBoxArray[i]->SetText(FText::FromString(strText));
	}
}
