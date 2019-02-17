// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBlueprintFunctionLibrary.h"

// Include Steam SDK
#include "ThirdParty/Steamworks/Steamv139/sdk/public/steam/steam_api.h"

bool UMyBlueprintFunctionLibrary::IsSteamAPIRunning() {
	return SteamAPI_Init();
}
