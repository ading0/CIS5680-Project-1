// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MoverSimulationTypes.h"
#include <DefaultMovementSet/CharacterMoverComponent.h>

#include "PlayerPawn.generated.h"

UCLASS()
class MOVERGAME_API APlayerPawn : public APawn, public IMoverInputProducerInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void UpdateCameraReference();

};
