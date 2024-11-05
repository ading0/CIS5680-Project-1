// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "GroupCamera.h"
#include <Kismet/GameplayStatics.h>
#include "DefaultGameMode.h"

void APlayerPawn::UpdateCameraReference()
{
	// Set Camera
	AGroupCamera* mainCamera = nullptr;

	TArray<AActor*> cameras;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGroupCamera::StaticClass(), cameras);
	if (cameras.Num())
	{
		mainCamera = (AGroupCamera*)cameras[0];
	}

	APlayerController* controller = Cast<APlayerController>(GetController());
	if (controller && mainCamera)
	{
		controller->SetViewTarget(mainCamera->GetAttachParentActor());
	}
}

void APlayerPawn::ServerTravel(const FString& inURL, bool bAbsolute, bool bShouldSkipGameNotify)
{
	GetWorld()->ServerTravel(inURL, bAbsolute, bShouldSkipGameNotify);
}
