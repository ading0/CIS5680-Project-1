// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include <Camera/CameraComponent.h>

#include "DefaultGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MOVER_API ADefaultGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UCameraComponent* GroupCameraRef;
	TArray<AActor*> Players;
	
protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void BeginPlay() override;
};
