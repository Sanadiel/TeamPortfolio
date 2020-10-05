// Fill out your copyright notice in the Description page of Project Settings.


#include "HpBarBase.h"
#include "Components/ProgressBar.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UHpBarBase::NativeConstruct()
{
	Super::NativeConstruct();

	HpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HpBar")));
}

void UHpBarBase::UpdateHpBar(float Percent)
{
	HpBar->SetPercent(Percent);
}

void UHpBarBase::BeginDestroy()
{
	Fuc_DeleSingle_TwoParam.Unbind();

	Super::BeginDestroy();
}

void UHpBarBase::NativeOnMouseEnter(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (Fuc_DeleSingle_TwoParam.IsBound() == true)
	{
		Fuc_DeleSingle_TwoParam.Execute(InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition()), true);
	}

	UE_LOG(LogClass, Warning, TEXT("MouseEnter"));
}

void UHpBarBase::NativeOnMouseLeave(const FPointerEvent & MouseEvent)
{
	Super::NativeOnMouseLeave(MouseEvent);

	if (Fuc_DeleSingle_TwoParam.IsBound() == true)
	{
		Fuc_DeleSingle_TwoParam.Execute(FVector2D::ZeroVector, false);
	}

	UE_LOG(LogClass, Warning, TEXT("MouseLeave"));
}

FReply UHpBarBase::NativeOnMouseMove(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
	Super::NativeOnMouseMove(InGeometry, InMouseEvent);

	FEventReply Reply = UWidgetBlueprintLibrary::Handled();

	//MakePosition(InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition()));

	return Reply.NativeReply;
}