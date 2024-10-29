// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include <Camera/CameraComponent.h>

#include "DefaultGameMode.generated.h"

/**
 * 
 */
UCLASS(config = Game, notplaceable, BlueprintType, Blueprintable, Transient, hideCategories = (Info, Rendering, MovementReplication, Replication, Actor), meta = (ShortTooltip = "Default MOVER Game Mode."), MinimalAPI)
class ADefaultGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	UCameraComponent* GroupCameraRef;

protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void BeginPlay() override;
};
