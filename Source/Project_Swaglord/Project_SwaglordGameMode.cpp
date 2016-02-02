// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Project_Swaglord.h"
#include "Project_SwaglordGameMode.h"
#include "Project_SwaglordCharacter.h"

AProject_SwaglordGameMode::AProject_SwaglordGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
