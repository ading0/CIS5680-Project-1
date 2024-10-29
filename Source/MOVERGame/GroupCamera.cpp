// Fill out your copyright notice in the Description page of Project Settings.


#include "GroupCamera.h"

#include "MOVERGameState.h"
#include "DefaultGameMode.h"
#include <Kismet/GameplayStatics.h>

FName AGroupCamera::MeshComponentName(TEXT("Mesh"));
FName AGroupCamera::SpringArmComponentName(TEXT("SpringArm"));
FName AGroupCamera::CameraComponentName(TEXT("Camera"));

// Sets default values
AGroupCamera::AGroupCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(AGroupCamera::MeshComponentName);
	if (Mesh)
	{
		Mesh->AlwaysLoadOnClient = true;
		Mesh->AlwaysLoadOnServer = true;
		Mesh->bOwnerNoSee = false;
		Mesh->bCastDynamicShadow = true;
		Mesh->bAffectDynamicIndirectLighting = true;
		Mesh->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		static FName MeshCollisionProfileName(TEXT("GroupCameraMesh"));
		Mesh->SetCollisionProfileName(MeshCollisionProfileName);
		Mesh->SetGenerateOverlapEvents(false);
		Mesh->SetCanEverAffectNavigation(false);
	}

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(AGroupCamera::SpringArmComponentName);
	if (SpringArm)
	{
		SpringArm->SetupAttachment(Mesh);
	}

	Camera = CreateDefaultSubobject<UCameraComponent>(AGroupCamera::CameraComponentName);
	if (Camera)
	{
		Camera->SetupAttachment(SpringArm);
	}
}

// Called when the game starts or when spawned
void AGroupCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGroupCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UWorld* World = GetWorld();

	if (!(World && World->GetNumPlayerControllers())) return;

	FVector AveragePlayerLocation = FVector(0);

	for (FConstPlayerControllerIterator Iterator = World->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PlayerController = Iterator->Get();
		if (PlayerController && PlayerController->GetPawn())
		{
			AveragePlayerLocation += PlayerController->GetPawn()->GetActorLocation();
		}
	}
	AveragePlayerLocation /= World->GetNumPlayerControllers();

	SetActorLocation(AveragePlayerLocation);

}

