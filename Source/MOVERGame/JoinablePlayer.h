// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/WidgetSwitcher.h"

#include "JoinablePlayer.generated.h"

UENUM(BlueprintType)
enum JoinStatus : uint8
{
	AVAILABLE = 0,
	OCCUPIED = 1
};

/**
 * 
 */
UCLASS()
class MOVERGAME_API UJoinablePlayer : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UWidgetSwitcher> StatusSwitcher;

	UPROPERTY(BlueprintReadOnly, meta=(DisplayName = "Join Status"))
	TEnumAsByte<JoinStatus> Status;

public:
	UFUNCTION(BlueprintCallable)
	void GetStatus(TEnumAsByte<JoinStatus>& JoinStatus);

protected:
	UFUNCTION(BlueprintCallable)
	void MakeAvailable();

	UFUNCTION(BlueprintCallable)
	void MakeOccupied();

	virtual void NativePreConstruct() override;
};
