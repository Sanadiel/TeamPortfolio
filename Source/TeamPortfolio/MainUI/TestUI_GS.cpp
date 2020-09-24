// Fill out your copyright notice in the Description page of Project Settings.


#include "TestUI_GS.h"

ATestUI_GS::ATestUI_GS()
{
	//MonsterNameArray
}

void ATestUI_GS::BeginPlay()
{
	Super::BeginPlay();
}

FString ATestUI_GS::GetName(int Value)
{
	if (MonsterNameArray.Num() >= Value)
	{
		return MonsterNameArray[Value];
	}
	
	return FString::Printf(TEXT("0"));
}
