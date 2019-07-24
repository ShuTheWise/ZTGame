// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ZTGameGameMode.h"
#include "ZTGameHUD.h"
#include "ZTGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AZTGameGameMode::AZTGameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AZTGameHUD::StaticClass();
}
