// Fill out your copyright notice in the Description page of Project Settings.


#include "GroupCamera.h"

#include "DefaultGameMode.h"

FName AGroupCamera::MeshComponentName(TEXT("Mesh"));
FName AGroupCamera::SpringArmComponentName(TEXT("SpringArm"));
FName AGroupCamera::CameraComponentName(TEXT("Camera"));

// Sets default values
AGroupCamera::AGroupCamera()
	: ActivePlayers(nullptr)
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

	ADefaultGameMode* gamemode = Cast<ADefaultGameMode>(GetWorld()->GetAuthGameMode());
	if (gamemode)
	{
		ActivePlayers = &gamemode->Players;
	}
	
}

// Called every frame
void AGroupCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!(ActivePlayers && ActivePlayers->Num() > 0)) return;

	// 计算所有玩家位置的平均位置
	FVector averagePlayerLocation = FVector::ZeroVector;
	FVector minLocation(FLT_MAX);
	FVector maxLocation(-FLT_MAX);

	for (AController* player : *ActivePlayers)
	{
		if (player && player->GetPawn())
		{
			FVector playerLocation = player->GetPawn()->GetActorLocation();
			averagePlayerLocation += playerLocation;

			// 更新最小和最大位置
			minLocation = minLocation.ComponentMin(playerLocation);
			maxLocation = maxLocation.ComponentMax(playerLocation);
		}
	}

	averagePlayerLocation /= ActivePlayers->Num();
	SetActorLocation(averagePlayerLocation);

	// 计算玩家之间的最大距离
	float maxDistance = (maxLocation - minLocation).Size();

	// 根据玩家间距离动态调整 SpringArm 的长度
	float desiredArmLength = FMath::Clamp(maxDistance * 1.4f, 1800.0f, 9000.0f);  // 300和1500是距离的范围，你可以根据需求调整
	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, desiredArmLength, DeltaTime, 3.0f);
}


