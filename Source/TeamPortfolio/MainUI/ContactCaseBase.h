// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ContactCaseBase.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPORTFOLIO_API UContactCaseBase : public UUserWidget
{
	GENERATED_BODY()
	
#pragma region Public Member
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<class UContactWidgetBase*> Contact;

#pragma endregion

#pragma region Public Member
public:

	UFUNCTION(BlueprintNativeEvent)
	void MakeChilren();
	void MakeChilren_Implementation();


#pragma endregion
};
