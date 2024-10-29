// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultGameMode.h"

#include <Kismet/GameplayStatics.h>
#include "GroupCamera.h"
#include "PlayerCharacter.h"
#include "GameFramework/PlayerStart.h"

void ADefaultGameMode::InitGame(const FString &MapName, const FString &Options, FString &ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	TArray<AActor*> cameras;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGroupCamera::StaticClass(), cameras);
	if (cameras.Num())
	{
		AGroupCamera *mainCamera = (AGroupCamera*)cameras[0];
		GroupCameraRef = mainCamera->GetCameraComponent();
	}

}

void ADefaultGameMode::BeginPlay()
{
	Super::BeginPlay();

}
