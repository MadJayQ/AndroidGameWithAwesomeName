// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_Swaglord.h"
#include "TileLayer.h"
#include "Engine.h"


// Sets default values
ATileLayer::ATileLayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATileLayer::BeginPlay()
{
	Super::BeginPlay();

	LastSpawnTransform = GetTransform();
	
	SpawnTile(InitialSpawnAmount);
}

// Called every frame
void ATileLayer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ATileLayer::SpawnTile(float numTiles)
{
	for (int i = 1; i <= numTiles; i++)
	{
		SpawnTileEvent();
	}
	//NextSpawn(SpawnDelay);
	UpdateGameOrigin(LastSpawnTransform);
	FVector SpawnLocation, SpawnScale;
	FRotator SpawnRotation;
	SpawnLocation = FVector(0, 0, 0);
	SpawnScale = LastSpawnTransform.GetScale3D();
	SpawnRotation = LastSpawnTransform.GetRotation().Rotator();
	LastSpawnTransform = FTransform(SpawnRotation, SpawnLocation, SpawnScale);

}

void ATileLayer::NextSpawn(float delay)
{
	FTimerHandle UniqueHandle;
	FTimerDelegate SpawnDelegate = FTimerDelegate::CreateUObject(this, &ATileLayer::SpawnTile, 5.f);
	for (int i = 0; i < ActiveTimers.Num(); i++)
	{
		auto handle = ActiveTimers[i];
		if (handle.IsValid())
		{
			if (!GetWorldTimerManager().TimerExists(handle) || !GetWorldTimerManager().IsTimerActive(handle))
			{
				ActiveTimers.Remove(handle);
				GetWorldTimerManager().ClearTimer(handle);
			}
		}
	}

	GetWorldTimerManager().SetTimer(UniqueHandle, SpawnDelegate, delay, false);
	ActiveTimers.Add(UniqueHandle);

}
