// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "JoinablePlayer.h"

#include "PlayerSelection.generated.h"

/**
 * 
 */
UCLASS()
class MOVERGAME_API UPlayerSelection : public UUserWidget
{
	GENERATED_BODY()

protected:
	// Map of controller index to player index
	TMap<int, int> PlayerIndexMap;

	// Available UI Player Slots
	UPROPERTY(BlueprintReadOnly)
	TArray<UJoinablePlayer*> JoinablePlayers;

	UPROPERTY(BlueprintReadOnly)
	int MaxPlayerCount;

public:
	UPlayerSelection(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativePreConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetPlayerIndex(int ControllerIndex, int PlayerIndex);

	UFUNCTION(BlueprintCallable)
	void GetPlayerIndex(int ControllerIndex, int& PlayerIndex, bool& Success);
};
