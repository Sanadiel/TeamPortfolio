// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Stage_GM.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPORTFOLIO_API AStage_GM : public AGameModeBase
{
	GENERATED_BODY()
#pragma region Public Member
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Boss")
	TSubclassOf<class ABossCharacter> Boss;

	//Time
	FTimerHandle GameTimer;

#pragma endregion
	

#pragma region Public Function
public:
	AStage_GM();	

	UFUNCTION(BlueprintCallable)
	void StartCountDown();

	UFUNCTION()
	void DecreaseTime();

	UFUNCTION()
	void Travel_MasterLobby();


	//virtual void SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void BeginPlay() override;

	/*APawn* SpawnDefaultPawnFor(AController* NewPlayer, AActor* StartSpot);
	APawn* SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot);*/

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName = TEXT("")) override;

	
#pragma endregion
};
