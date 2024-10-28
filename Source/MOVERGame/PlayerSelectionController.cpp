// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSelectionController.h"
#include "EnhancedInputSubsystems.h"
#include <Net/UnrealNetwork.h>

APlayerSelectionController::APlayerSelectionController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	  ControllerID(-1),
	  PlayerID(-1)
{

}

void APlayerSelectionController::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerSelectionController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerSelectionController, PlayerID);
}

void APlayerSelectionController::OnRep_PlayerID()
{
	UE_LOG(LogTemp, Warning, TEXT("Replicated Player ID: %d"), PlayerID);
}

void APlayerSelectionController::ServerTravel(const FString& inURL, bool bAbsolute, bool bShouldSkipGameNotify)
{
	GetWorld()->ServerTravel(inURL, bAbsolute, bShouldSkipGameNotify);
}
