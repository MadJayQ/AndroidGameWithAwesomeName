// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"


class ATileLayer;

UCLASS()
class PROJECT_SWAGLORD_API ATile : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	class UArrowComponent* AttachPoint; //THIS MUST BE SET IN THE DERIVED BLUEPRINT DURING THE CONSTRUCTION SCRIPT!!!!!!!! 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	class ATileLayer* OwnerLayer;
	
public:	
	// Sets default values for this actor's properties
	ATile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	FTransform GetAttachTransform();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	bool CanAttach();

	
	
};