// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Project_Swaglord.h"
#include "Project_SwaglordCharacter.h"
#include "Engine.h"

AProject_SwaglordCharacter::AProject_SwaglordCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->RelativeRotation = FRotator(0.f,0.f,0.f);

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	PrimaryActorTick.bCanEverTick = true;

	player_color_saved.Add(0);
	player_color_saved.Add(0);

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AProject_SwaglordCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	//InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	//InputComponent->BindAxis("MoveRight", this, &AProject_SwaglordCharacter::MoveRight);

	InputComponent->BindTouch(IE_Pressed, this, &AProject_SwaglordCharacter::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &AProject_SwaglordCharacter::TouchStopped);
}

void AProject_SwaglordCharacter::Tick(float dt)
{
	Move(1);
	SetPlayerColor(player_color);
}

void AProject_SwaglordCharacter::Move(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(1.f, 0.f,0.f), Value);
}

void AProject_SwaglordCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (!GEngine)
		return;
	FVector2D ScreenSize = (FVector2D)(GEngine->GameViewport->Viewport->GetSizeXY());
	uint8 temp_color = 0;

	switch (FingerIndex)
	{
	case ETouchIndex::Touch1:
	{
		if (Location.X < ScreenSize.X / 2)
		{
			if (!player_color_saved.Contains(1))
			{
				player_color_saved[0] = 1;
				player_color += 1;
			}
		}
		else if (Location.X > ScreenSize.X / 2)
		{
			if (!player_color_saved.Contains(2))
			{
				
				player_color_saved[0] = 2;
				player_color += 2;
			}
		}
	}
	case ETouchIndex::Touch2:
	{
		if (Location.X < ScreenSize.X / 2)
		{
			if (!player_color_saved.Contains(1))
			{
				player_color_saved[1] = 1;
				player_color += 1;
			}
		}
		else if (Location.X > ScreenSize.X / 2)
		{
			if (!player_color_saved.Contains(2))
			{
				player_color_saved[1] = 2;
				player_color += 2;
			}
		}
	}
	default:
		break;
	}
}

void AProject_SwaglordCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (!GEngine)
		return;


	switch (FingerIndex)
	{
	case ETouchIndex::Touch1:
	{
		player_color -= player_color_saved[0];
		player_color_saved[0] = 0;
	}
	case ETouchIndex::Touch2:
	{
		player_color -= player_color_saved[1];
		player_color_saved[1] = 0;
	}
	default:
		break;
	}
}

