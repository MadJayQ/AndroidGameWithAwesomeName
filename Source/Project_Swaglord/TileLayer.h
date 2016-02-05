// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tile.h"

#include "GameFramework/Actor.h"
#include "TileLayer.generated.h"


class ATile;

UCLASS()
class PROJECT_SWAGLORD_API ATileLayer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileLayer();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	FTransform LastSpawnTransform;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tile")
	TArray<ATile*> ActiveTiles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnDelay = 2.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnAmount = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float InitialSpawnAmount = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float TilesRemainingBeforeSpawn = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	TArray<FTimerHandle> ActiveTimers;

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnTile(float numTiles);

	UFUNCTION(BlueprintImplementableEvent, Category = "Spawning")
	void SpawnTileEvent();


	void CreateUniqueTimer(float delay, FTimerDelegate Delegate, bool bLooping);
	void CleanupDeadTimers();


private:


	void NextSpawn(float delay);
	void SpawnTile_Delegate();

<<<<<<< HEAD
	FORCEINLINE void UpdateGameOrigin(FTransform newTransform)
=======
	__forceinline void UpdateGameOrigin(FTransform newTransform)
>>>>>>> 119f64589d1286a86dfdbd66ad8bce2b77c9aff3
	{
		UWorld* world = GetWorld();
		check(world);

		FVector transform_vector = newTransform.GetLocation();

		FIntVector vecNewOrigin = FIntVector(transform_vector.X, transform_vector.Y, transform_vector.Z) + world->OriginLocation;
		world->RequestNewWorldOrigin(vecNewOrigin);


	}

	
	
};
