// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HpBarBase.generated.h"

DECLARE_DELEGATE_TwoParams(FDele_Single_TwoParam, FVector2D, bool)
/**
 * 
 */
UCLASS()
class TEAMPORTFOLIO_API UHpBarBase : public UUserWidget
{
	GENERATED_BODY()
#pragma region Public Member
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UProgressBar* HpBar;

#pragma endregion 

#pragma region Public Function
public:
	virtual void NativeConstruct() override;

	FDele_Single_TwoParam Fuc_DeleSingle_TwoParam;

	UFUNCTION(BlueprintCallable)
	void UpdateHpBar(float Percent);

	virtual void BeginDestroy() override;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	//void MakePosition(FVector2D MousePosiion);


#pragma endregion 
};
